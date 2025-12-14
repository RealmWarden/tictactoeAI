#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

void randomWeights(float weightsLayer[9][9]);
void boardToInputLayer(const string matrix[9], float inputLayer[10], bool meFirst);
void passThroughLayerOne(const float inputLayer[10], const float weightsLayer[10][9], float outputLayer[9]);
void passThroughLayerTwo(const float inputLayer[9], const float weightsLayer[9][9], float outputLayer[9]);
int getOutput(const float outputLayer[9], const string matrix[9]);