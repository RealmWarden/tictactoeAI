#include <iostream>
#include <string>
using namespace std;

int main(){
    /* initialize variables */
    string symbol;
    bool win = false;
    bool tie = false;

    /* create a 1x9 matrix of dashes*/
    string matrix[9] = {"-","-","-","-","-","-","-","-","-"};

    /* print a 3x3 grid of dashes */
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i * 3 + j];
        }
        cout << endl;
    }

    /* main loop */
    for (int i = 0; i < 9; i++) {
        /* if x is even, symbol is "x", otherwise "o" */
        symbol = "o";
        if (i % 2 == 0) {
            symbol = "x";
        }
        
        /* wait for the user to input a single-digit natural number */
        int userInput;
        cout << "Please enter a position (1-9) to place your " << symbol << ": ";
        cin >> userInput;
        while (userInput < 1 || userInput > 9 || matrix[userInput-1] != "-") {
            if (matrix[userInput-1] != "-") {
                cout << "Position already taken. Please enter a different position: ";
            } 
            else {
                cout << "Position outside of range. Please enter a number between 1 and 9: ";
            }
            cin >> userInput;
        }

        /* print the symbol in the correct position */
        matrix[userInput-1] = symbol;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << matrix[i * 3 + j];
            }
            cout << endl;
        }

        /* check for a win */
        if ((matrix[0] == symbol && matrix[1] == symbol && matrix[2] == symbol) ||
            (matrix[3] == symbol && matrix[4] == symbol && matrix[5] == symbol) ||
            (matrix[6] == symbol && matrix[7] == symbol && matrix[8] == symbol) ||
            (matrix[0] == symbol && matrix[3] == symbol && matrix[6] == symbol) ||
            (matrix[1] == symbol && matrix[4] == symbol && matrix[7] == symbol) ||
            (matrix[2] == symbol && matrix[5] == symbol && matrix[8] == symbol) ||
            (matrix[0] == symbol && matrix[4] == symbol && matrix[8] == symbol) ||
            (matrix[2] == symbol && matrix[4] == symbol && matrix[6] == symbol)) {
            win = true;
            break;
        }

        /* check for a tie */
        for (int i = 0; i < 9; i++) {
            if (matrix[i] == "-") {
                break;
            }
            if (i == 8) {
                tie = true;
            }
        }
        if (tie) {
            break;
        }
    }

    if (win) {
        cout << "The winner is: " << symbol << "!" << endl;
    } else {
        cout << "Tie!" << endl;
    }
}
