#include "tictactoe.h"
#include "weightsManager.h"
using namespace std;

int main(){
    /* initialize variables */
    string symbol;
    string matrix[9];
    bool AIMoveLast;
    int randomWin = 0;
    int AIWin = 0;
    int num_ties = 0;
    int num_iterations = 1000000;

    /* determine weights */
    float weightsLayerOne[10][9];
    float weightsLayerTwo[9][9];
    loadWeights("trained_weights.txt", weightsLayerOne, weightsLayerTwo);

    for (int iteration = 0; iteration < num_iterations; iteration++) {
        /* create a 1x9 matrix of dashes */
        initializeBoard(matrix);

        /* decide who is first */
        bool randomTurn = true;
        bool meFirst = false;
        int coinFlip = rand() % 2;
        if (coinFlip == 1){
            randomTurn = false;
            meFirst = true;
        }

        /* main loop */
        for (int i = 0; i < 9; i++) {
            /* if x is even, symbol is "x", otherwise "o" */
            symbol = getSymbol(i);
            
            int userInput;
            float inputLayer[10];
            boardToInputLayer(matrix, inputLayer, meFirst);
            
            /* decide who is control */
            if (randomTurn){
                /* wait for the user to input a single-digit natural number */
                userInput = getRandomMove(matrix);
            } else {
                /* THIS IS WHERE THE DECISION MAKING GOES */
                float outputLayerOne[9];
                passThroughLayerOne(inputLayer, weightsLayerOne, outputLayerOne);
                float outputLayerTwo[9];
                passThroughLayerTwo(outputLayerOne, weightsLayerTwo, outputLayerTwo);
                userInput = getOutput(outputLayerTwo, matrix);
            }

            /* identify who moved last */
            AIMoveLast = true;
            if (randomTurn){
                AIMoveLast = false;
            }
            
            /* flip turn identifier */
            randomTurn = !randomTurn;

            /* print the symbol in the correct position */
            addMove(matrix, userInput, symbol);

            /* check for a win */
            if (checkWin(matrix, symbol)) {
                break;
            }

            /* check for a tie */
            if (checkTie(matrix)) {
                break;
            }
        }

        /* record result */
        if (checkWin(matrix, symbol)) {
            if (AIMoveLast){
                AIWin += 1;
            } else {
                randomWin += 1;
            }
        } else {
            num_ties += 1;
        }
    }
    float percent_AIWin = 100.0f * AIWin / num_iterations;
    float percent_randomWin = 100.0f * randomWin / num_iterations;
    float percent_tie = 100.0f * num_ties / num_iterations;
    cout << "The trained AI model won " << AIWin << " times. (" << percent_AIWin << "%)." << endl;
    cout << "The random player won " << randomWin << " times. (" << percent_randomWin << "%)." << endl;
    cout << "There were " << num_ties << " ties. (" << percent_tie << "%)." << endl;
}