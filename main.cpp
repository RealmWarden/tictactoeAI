#include "tictactoe.h"
#include "weightsManager.h"
using namespace std;

int main() {
    /* BETTER seed random generator */
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    srand(seed);

    /* initialize variables */
    string symbol;
    string matrix[9];
    int creativity = 1;
    int generationSize = 50;

    /* initialize random weights for neural network */
    float weightsLayerOne[9][9];
    randomWeights(weightsLayerOne);
    float weightsLayerTwo[9][9];
    randomWeights(weightsLayerTwo);

    /* create a 1x9 matrix of dashes*/
    initializeBoard(matrix);
    /* play a game */
    for (int i = 0; i < 9; i++) {
        /* if x is even, symbol is "x", otherwise "o" */
        symbol = getSymbol(i);   
        /* THIS IS WHERE THE DECISION MAKING GOES */
        
        int userInput;
        int inputLayer[9];
        boardToInputLayer(matrix, inputLayer);
        float outputLayerOne[9];
        passThroughLayer(inputLayer, weightsLayerOne, outputLayerOne);
        float outputLayerTwo[9];
        passThroughLayer(inputLayer, weightsLayerTwo, outputLayerTwo);
        userInput = getOutput(outputLayerTwo, matrix);

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