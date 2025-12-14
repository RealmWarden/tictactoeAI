#include "tictactoe.h"
#include <iostream>
#include <cstdlib> // instead of <random>, creates different output each time
#include <ctime> // for seeding rand()
using namespace std;

int getRandomMove(const string matrix[9]);

int main(){
    /* seed random generator */
    srand(time(NULL));

    /* initialize variables */
    string symbol;
    string matrix[9];

    /* create a 1x9 matrix of dashes*/
    initializeBoard(matrix);

    /* print a 3x3 grid of dashes */
    printBoard(matrix);

    /* main loop */
    for (int i = 0; i < 9; i++) {
        /* if x is even, symbol is "x", otherwise "o" */
        symbol = getSymbol(i);
        
        /* wait for the user to input a single-digit natural number */
        int userInput = getRandomMove(matrix);

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


void initializeBoard(string matrix[9]) {
    for (int i = 0; i < 9; i++) {
        matrix[i] = "-";
    }
}

void printBoard(const string matrix[9]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i * 3 + j];
        }
        cout << endl;
    }
}

string getSymbol(int turn) {
    if (turn % 2 == 0) {
        return "x";
    } 
    else {
        return "o";
    }
}

bool isMoveValid(const string matrix[9], int userInput) {
    if (userInput < 1 || userInput > 9 || matrix[userInput-1] != "-") {
        return false;
    } else {
        return true;
    }
}

void addMove(string matrix[9], int position, const string symbol) {
    matrix[position-1] = symbol;
}

bool checkWin(const string matrix[9], const string symbol) {
    if ((matrix[0] == symbol && matrix[1] == symbol && matrix[2] == symbol) ||
        (matrix[3] == symbol && matrix[4] == symbol && matrix[5] == symbol) ||
        (matrix[6] == symbol && matrix[7] == symbol && matrix[8] == symbol) ||
        (matrix[0] == symbol && matrix[3] == symbol && matrix[6] == symbol) ||
        (matrix[1] == symbol && matrix[4] == symbol && matrix[7] == symbol) ||
        (matrix[2] == symbol && matrix[5] == symbol && matrix[8] == symbol) ||
        (matrix[0] == symbol && matrix[4] == symbol && matrix[8] == symbol) ||
        (matrix[2] == symbol && matrix[4] == symbol && matrix[6] == symbol)) {
        return true;
    } 
    else {
        return false;
    }
}

bool checkTie(const string matrix[9]) {
    for (int j = 0; j < 9; j++) {
        if (matrix[j] == "-") {
            return false;
        }
    }
    return true;
}

int getRandomMove(const string matrix[9]) {
    int userInput = rand() % 9 + 1;
    while (!isMoveValid(matrix, userInput)) {
        userInput = rand() % 9 + 1;
    }
    return userInput;
}