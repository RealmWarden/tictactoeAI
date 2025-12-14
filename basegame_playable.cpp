#include "tictactoe.h"
#include <iostream>
using namespace std;

int main(){
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
        int userInput = getHumanMove(matrix, symbol);

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

int getHumanMove(const string matrix[9], const string symbol) {
    int userInput;
    cout << "Please enter a position (1-9) to place your " << symbol << ": ";
    cin >> userInput;
    while (!isMoveValid(matrix, userInput)) {
        cout << "Invalid move. Please enter a position (1-9) to place your " << symbol << ": ";
        cin >> userInput;
    }
    return userInput;
}