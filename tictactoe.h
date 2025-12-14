#pragma once // I don't actually know what this does, but the internet tells me it is important
#include <iostream>
#include <string>
using namespace std;

void initializeBoard(string matrix[9]);
void printBoard(const string matrix[9]);
string getSymbol(int turn);
bool isMoveValid(const string matrix[9], int position);
void addMove(string matrix[9], int position, const string symbol);
bool checkWin(const string matrix[9], const string symbol);
bool checkTie(const string matrix[9]);
int getMove(const string matrix[9], const string symbol);
int getHumanMove(const string matrix[9], const string symbol);