#include "tictactoe.h"
#include <cstdlib> // instead of <random>, creates different output each time
#include <ctime> // for seeding rand()
using namespace std;

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