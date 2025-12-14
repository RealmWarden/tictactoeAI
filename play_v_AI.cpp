#include "tictactoe.h"
#include "weightsManager.h"
using namespace std;

void randomizeWeights(float weightsLayerOne[9][9], float weightsLayerTwo[9][9]);

int main(){
    /* initialize variables */
    string symbol;
    string matrix[9];

    /* randomize weights */
    float weightsLayerOne[9][9];
    float weightsLayerTwo[9][9];
    randomizeWeights(weightsLayerOne, weightsLayerTwo);

    /* create a 1x9 matrix of dashes*/
    initializeBoard(matrix);

    /* print a 3x3 grid of dashes */
    printBoard(matrix);

    /* decide who is first */
    bool usersTurn = true;
    int coinFlip = rand() % 2;
    if (coinFlip == 1){
        usersTurn = false;
    }

    /* main loop */
    for (int i = 0; i < 9; i++) {
        /* if x is even, symbol is "x", otherwise "o" */
        symbol = getSymbol(i);
        
        int userInput;
        float inputLayer[9];
        boardToInputLayer(matrix, inputLayer);
        
        /* decide who is control */
        if (usersTurn){
            /* wait for the user to input a single-digit natural number */
            userInput = getHumanMove(matrix, symbol);
        } else {
            /* THIS IS WHERE THE DECISION MAKING GOES */
            float outputLayerOne[9];
            passThroughLayer(inputLayer, weightsLayerOne, outputLayerOne);
            float outputLayerTwo[9];
            passThroughLayer(outputLayerOne, weightsLayerTwo, outputLayerTwo);
            userInput = getOutput(outputLayerTwo, matrix);
        }
        
        /* flip turn identifier */
        usersTurn = !usersTurn;

        /* print the symbol in the correct position */
        addMove(matrix, userInput, symbol);
        printBoard(matrix);

        /* check for a win */
        if (checkWin(matrix, symbol)) {
            break;
        }

        /* check for a tie */
        if (checkTie(matrix)) {
            break;
        }
    }

    if (checkWin(matrix, symbol)) {
        cout << "The winner is: " << symbol << "!" << endl;
    } else {
        cout << "Tie!" << endl;
    }
}

void randomizeWeights(float weightsLayerOne[9][9], float weightsLayerTwo[9][9]){
    randomWeights(weightsLayerOne);
    randomWeights(weightsLayerTwo);
}