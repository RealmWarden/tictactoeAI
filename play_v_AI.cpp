#include "tictactoe.h"
#include "weightsManager.h"
using namespace std;

void randomizeWeights(float weightsLayerOne[10][9], float weightsLayerTwo[9][9]);

int main(){
    /* initialize variables */
    string symbol;
    string matrix[9];

    /* determine weights */
    float weightsLayerOne[10][9];
    float weightsLayerTwo[9][9];
    loadWeights("trained_weights.txt", weightsLayerOne, weightsLayerTwo);
    bool trained;
    cout << "Do you want to play against a trained AI? (y/n)";
    char yn;
    cin >> yn;
    if (yn == 'y'){
        trained = true;
    } else if (yn == 'n') {
        trained = false;
    } else {
        while (yn != 'n' && yn != 'y'){
            cout << "Please enter y to play trained AI or n to play an untrained AI: ";
            cin >> yn;
        }
        if (yn == 'y'){
            trained = true;
        } else if (yn == 'n') {
            trained = false;
        }
    }
    if (!trained){
        randomizeWeights(weightsLayerOne, weightsLayerTwo);
    }

    /* time ot play against AI */
    bool playAgain = true;
    while (playAgain) {
        /* create a 1x9 matrix of dashes */
        initializeBoard(matrix);

        /* print a 3x3 grid of dashes */
        printBoard(matrix);

        /* decide who is first */
        bool usersTurn = true;
        bool meFirst = false;
        int coinFlip = rand() % 2;
        if (coinFlip == 1){
            usersTurn = false;
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
            if (usersTurn){
                /* wait for the user to input a single-digit natural number */
                userInput = getHumanMove(matrix, symbol);
            } else {
                /* THIS IS WHERE THE DECISION MAKING GOES */
                float outputLayerOne[9];
                passThroughLayerOne(inputLayer, weightsLayerOne, outputLayerOne);
                float outputLayerTwo[9];
                passThroughLayerTwo(outputLayerOne, weightsLayerTwo, outputLayerTwo);
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

        cout << "Play again? (y/n): ";
        char yn;
        cin >> yn;
        if (yn == 'y'){
            playAgain = true;
        } else if (yn == 'n') {
            playAgain = false;
        } else {
            while (yn != 'n' && yn != 'y'){
                cout << "Please enter y to play again or n to exit: ";
                cin >> yn;
            }
            if (yn == 'y'){
                playAgain = true;
            } else if (yn == 'n') {
                playAgain = false;
            }
        }
    }
}

void randomizeWeights(float weightsLayerOne[10][9], float weightsLayerTwo[9][9]){
    randomWeights(weightsLayerOne);
    randomWeights(weightsLayerTwo);
}