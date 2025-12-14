#include "weightsManager.h"
using namespace std;

int main() {
    /* seed random generator */
    srand(time(NULL));

    /* initialize variables */
    int creativity = 1;
    int generationSize = 50;

    /* initialize random weights for neural network */
    float weightsLayerOne[9][9];
    randomWeights(weightsLayerOne);
    float weightsLayerTwo[9][9];
    randomWeights(weightsLayerTwo);

    // get board state
    // turn board state into input layer
    // feed input layer through neural network using weights
    // get output value
    // pass output value back into board position
}


void randomWeights(float weightsLayer[9][9]) {
    /* fill with random values from -0.5 to 0.5 */
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            weightsLayer[i][j] = ((double)rand()) / RAND_MAX - 0.5;
        }
    }
}

void boardToInputLayer(const string matrix[9], int inputLayer[9]){
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

void passThroughLayer(const int inputLayer[9], const float weightsLayer[9][9], int outputLayer[9]){
    for (int i = 0; i < 9; i++) {
        outputLayer[i] = 0;
        for (int j = 0; j < 9; j++) {
            outputLayer[i] += inputLayer[j] * weightsLayer[j][i];
        }
    }
}

int getOutput(const int outputLayer[9]){
    int maxOutput = 0;
    for (int i = 1; i < 9; i++) {
        if (outputLayer[i] > outputLayer[maxOutput]) {
            maxOutput = i;
        }
    }
    return maxOutput;
}