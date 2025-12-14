#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

void randomWeights(float weightsLayer[9][9]);
void boardToInputLayer(const string matrix[9], int inputLayer[9]);
void passThroughLayer(const int inputLayer[9], const float weightsLayer[9][9], int outputLayer[9]);
int getOutput(const int outputLayer[9]);