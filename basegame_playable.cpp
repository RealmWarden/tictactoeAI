#include <iostream>
#include <string>
using namespace std;

int main(){
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
        string symbol = "o";
        if (i % 2 == 0) {
            symbol = "x";
        }
        
        /* wait for the user to input a single-digit natural number */
        int userInput;
        cout << "Please enter a number 1 to 9: ";
        cin >> userInput;
        while (userInput < 1 || userInput > 9) {
            cout << "Invalid input. Please enter a number between 1 and 9:";
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
    }
}
