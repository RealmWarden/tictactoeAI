#include "weightsManager.h"
#include "tictactoe.h"
using namespace std;

void randomWeights(float weightsLayer[9][9]) {
    /* fill with random values from -0.5 to 0.5 */
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            weightsLayer[i][j] = ((double)rand()) / RAND_MAX - 0.5;
        }
    }
}

void boardToInputLayer(const string matrix[9], float inputLayer[9]){
    for (int i = 0; i < 9; i++) {
        if (matrix[i] == "x") {
            inputLayer[i] = 1;
        } else if (matrix[i] == "o") {
            inputLayer[i] = -1;
        } else {
            inputLayer[i] = 0;
        }
    }
}

void passThroughLayer(const float inputLayer[9], const float weightsLayer[9][9], float outputLayer[9]){
    for (int i = 0; i < 9; i++) {
        outputLayer[i] = 0;
        for (int j = 0; j < 9; j++) {
            outputLayer[i] += inputLayer[j] * weightsLayer[j][i];
        }
    }
}

int getOutput(const float outputLayer[9], const string matrix[9]){
    int maxOutput = -1;
    for (int i = 0; i < 9; i++) {
        if (!isMoveValid(matrix, i+1)) {
            continue;
        }
        if (maxOutput == -1 || outputLayer[i] > outputLayer[maxOutput]) {
            maxOutput = i;
        }
    }
    return maxOutput+1;
}