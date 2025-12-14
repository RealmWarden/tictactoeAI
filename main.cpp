#include "tictactoe.h"
#include "weightsManager.h"
using namespace std;

void trainModel(float weightsLayerOne_parent[9][9], float weightsLayerTwo_parent[9][9], float creativity, int generationSize, int rewardForWin, int rewardForTie, int gamesPerIndividual, int numGenerations, float weightsLayerOne[9][9], float weightsLayerTwo[9][9]);

int main() {
    /* initialize variables */
    string symbol;
    string matrix[9];
    float creativity = 0.1f;
    int generationSize = 10;
    int rewardForWin = 2;
    int rewardForTie = 1;
    int gamesPerIndividual = 100;
    int numGenerations = 1000;

    /* initialize random weights for neural network */
    float weightsLayerOne_parent[9][9];
    randomWeights(weightsLayerOne_parent);
    float weightsLayerTwo_parent[9][9];
    randomWeights(weightsLayerTwo_parent);

    /* train model */
    float weightsLayerOne[9][9];
    float weightsLayerTwo[9][9];
    trainModel(weightsLayerOne_parent, weightsLayerTwo_parent, creativity, generationSize, rewardForWin, rewardForTie, gamesPerIndividual, numGenerations, weightsLayerOne, weightsLayerTwo);

    /* time to play against trained AI */
    bool playAgain = true;
    while (playAgain) {
        /* initialize variables */
        string symbol;
        string matrix[9];
        for (int i = 0; i < 9; i++){
            matrix[i] = "-";
        }

        /* create a 1x9 matrix of dashes */
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


void trainModel(float weightsLayerOne_parent[9][9], float weightsLayerTwo_parent[9][9], float creativity, int generationSize, int rewardForWin, int rewardForTie, int gamesPerIndividual, int numGenerations, float weightsLayerOne[9][9], float weightsLayerTwo[9][9]){
    /* initialize variables */
    string symbol;
    string matrix[9];
    
    /* BETTER seed random generator */
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    srand(seed);

    for (int gen_ID = 0; gen_ID < numGenerations; gen_ID++){
        /* propogate a generation */
        float weightsStackOne[generationSize][9][9];
        float weightsStackTwo[generationSize][9][9];
        for (int i = 0; i < generationSize; i++) {
            for (int j = 0; j < 9; j++){
                for (int k = 0; k < 9; k++){
                    float r1 = (float)rand() / RAND_MAX;
                    weightsStackOne[i][j][k] = weightsLayerOne_parent[j][k] + ((r1-0.5f)*creativity);
                    float r2 = (float)rand() / RAND_MAX;
                    weightsStackTwo[i][j][k] = weightsLayerTwo_parent[j][k] + ((r2-0.5f)*creativity);
                }
            }
        }

        /* create scoreboard */
        int scoreBoard[generationSize];
        for (int i = 0; i < generationSize; i++){
            scoreBoard[i] = 0;
        }

        for (int child_ID = 0; child_ID < generationSize; child_ID++){
            /* assign child weights */
            float weightsLayerOne_child[9][9];
            for (int i = 0; i < 9; i++){
                for (int j = 0; j < 9; j++){
                    weightsLayerOne_child[i][j] = weightsStackOne[child_ID][i][j];
                }
            }
            float weightsLayerTwo_child[9][9];
            for (int i = 0; i < 9; i++){
                for (int j = 0; j < 9; j++){
                    weightsLayerTwo_child[i][j] = weightsStackTwo[child_ID][i][j];
                }
            }

            /* individual plays a bunch of games against parent */
            for (int i = 0; i < gamesPerIndividual; i++){
                /* create a 1x9 matrix of dashes*/
                initializeBoard(matrix);

                /* decide who is first */
                bool parentsTurn = true;
                int coinFlip = rand() % 2;
                if (coinFlip == 1){
                    parentsTurn = false;
                }

                /* play a game */
                for (int i = 0; i < 9; i++) {
                    /* if x is even, symbol is "x", otherwise "o" */
                    symbol = getSymbol(i);   

                    int userInput;
                    float inputLayer[9];
                    boardToInputLayer(matrix, inputLayer);
                    
                    /* decide who is control */
                    if (parentsTurn){
                        /* THIS IS WHERE THE DECISION MAKING GOES */
                        float outputLayerOne[9];
                        passThroughLayer(inputLayer, weightsLayerOne_parent, outputLayerOne);
                        float outputLayerTwo[9];
                        passThroughLayer(outputLayerOne, weightsLayerTwo_parent, outputLayerTwo);
                        userInput = getOutput(outputLayerTwo, matrix);
                    } else {
                        /* THIS IS WHERE THE DECISION MAKING GOES */
                        float outputLayerOne[9];
                        passThroughLayer(inputLayer, weightsLayerOne_child, outputLayerOne);
                        float outputLayerTwo[9];
                        passThroughLayer(outputLayerOne, weightsLayerTwo_child, outputLayerTwo);
                        userInput = getOutput(outputLayerTwo, matrix);
                    }
                    
                    /* flip turn identifier */
                    parentsTurn = !parentsTurn;

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
                
                /* assign rewards */
                if (checkWin(matrix, symbol)) {
                    if (parentsTurn){
                        scoreBoard[child_ID] += rewardForWin;
                    }
                } else {
                    scoreBoard[child_ID] += rewardForTie;
                }
            }
        }

        /* copy best of previous generation to become new parent */
        int max_index = 0;
        int max_val = 0;
        for (int i = 0; i < generationSize; i++) {
            if (scoreBoard[i] > max_val) {
                max_val = scoreBoard[i];
                max_index = i; 
            }
        }
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                weightsLayerOne_parent[i][j] = weightsStackOne[max_index][i][j];
                weightsLayerTwo_parent[i][j] = weightsStackTwo[max_index][i][j];
            }
        }
    }

    /* return weights of best of last generation */
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            weightsLayerOne[i][j] = weightsLayerOne_parent[i][j];
            weightsLayerTwo[i][j] = weightsLayerTwo_parent[i][j];
        }
    }
}