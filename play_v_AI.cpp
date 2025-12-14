#include "tictactoe.h"
#include "weightsManager.h"
using namespace std;

void randomizeWeights(float weightsLayerOne[10][9], float weightsLayerTwo[9][9]);

int main(){
    /* initialize variables */
    string symbol;
    string matrix[9];

    /* determine weights */
    float weightsLayerOne[10][9] = {
        {0.362823,-1.43205,-0.10534,0.0888683,0.973322,0.266389,-0.42108,-0.0779766,-0.702939},
        {0.602733,-0.228834,-0.0619215,0.01618,-0.380264,0.515246,0.875479,0.499625,0.511958},
        {0.333486,0.883964,-0.732199,-0.0468693,-0.237294,-0.202271,-0.4193,-0.00770046,-0.444381},
        {-0.0966548,0.203388,-0.663997,0.14303,0.752243,-0.0174839,-0.474483,-0.329565,0.379607},
        {-0.394106,0.772351,-0.67788,0.273903,-0.397809,-0.238673,-0.145308,0.47003,-0.869864},
        {-0.221136,-0.138999,0.429956,-0.282914,0.574239,0.932889,-0.229349,0.63801,0.440218},
        {0.647537,0.0379141,0.137606,-0.84595,-0.175915,-1.07008,-0.312944,0.520756,1.05498},
        {-0.243876,-0.0718686,-1.03993,0.165555,0.587815,-0.0783803,0.479267,0.775697,-0.00157831},
        {-0.661366,-0.10274,0.856507,0.721537,0.00977454,0.63506,-0.388264,-0.0676001,-0.0202927},
        {-0.438416,0.262193,-0.596424,-0.130851,-0.00166144,0.15266,-0.0862969,-0.0701187,-0.300949}};
    float weightsLayerTwo[9][9] = {
        {-0.259339,0.229115,0.799114,0.75072,0.436745,-0.634344,-0.786985,-0.491284,-0.593349},
        {1.12307,-0.0478456,-0.145949,0.562577,-0.51992,-0.046804,0.0840886,0.567614,0.159693},
        {-0.223938,-0.22395,-0.518344,0.84545,0.104166,-0.0675802,0.383378,0.0788706,-0.427484},
        {0.316821,-0.11807,0.793481,-0.295513,0.321045,0.1539,-0.850708,0.182714,-0.339174},
        {-0.0379346,0.587392,0.659935,-0.523208,-0.160024,0.0967199,-0.113575,0.503679,0.311251},
        {-0.138637,-0.477274,0.292922,-0.170922,-0.105625,0.0724935,-0.0563071,-0.0114151,-0.972211},
        {0.931683,-1.20177,0.433904,0.112001,-0.982399,0.0477336,0.423335,-0.325419,0.642615},
        {-0.403689,0.310178,0.406158,1.09756,-0.267292,0.271959,0.585848,0.4203,-0.728994},
        {-0.891929,-0.252409,-0.0895195,-0.79562,0.135362,-0.600329,0.361406,-0.273457,0.334246}};
    bool trained;
    cout << "Do you want to play against a trained AI? (y/n)";
    char yn;
    cin >> yn;
    if (yn == 'y'){
        trained = true;
    } else if (yn == 'n') {
        trained = false;
    } else {
        while (yn != 'n' && yn != 'y'){
            cout << "Please enter y to play trained AI or n to play an untrained AI: ";
            cin >> yn;
        }
        if (yn == 'y'){
            trained = true;
        } else if (yn == 'n') {
            trained = false;
        }
    }
    if (!trained){
        randomizeWeights(weightsLayerOne, weightsLayerTwo);
    }

    /* create a 1x9 matrix of dashes */
    initializeBoard(matrix);

    /* print a 3x3 grid of dashes */
    printBoard(matrix);

    /* decide who is first */
    bool usersTurn = true;
    bool meFirst = false;
    int coinFlip = rand() % 2;
    if (coinFlip == 1){
        usersTurn = false;
        meFirst = true;
    }

    /* main loop */
    for (int i = 0; i < 9; i++) {
        /* if x is even, symbol is "x", otherwise "o" */
        symbol = getSymbol(i);
        
        int userInput;
        float inputLayer[10];
        boardToInputLayer(matrix, inputLayer, meFirst);
        
        /* decide who is control */
        if (usersTurn){
            /* wait for the user to input a single-digit natural number */
            userInput = getHumanMove(matrix, symbol);
        } else {
            /* THIS IS WHERE THE DECISION MAKING GOES */
            float outputLayerOne[9];
            passThroughLayerOne(inputLayer, weightsLayerOne, outputLayerOne);
            float outputLayerTwo[9];
            passThroughLayerTwo(outputLayerOne, weightsLayerTwo, outputLayerTwo);
            userInput = getOutput(outputLayerTwo, matrix);
        }
        
        /* flip turn identifier */
        usersTurn = !usersTurn;

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

void randomizeWeights(float weightsLayerOne[10][9], float weightsLayerTwo[9][9]){
    randomWeights(weightsLayerOne);
    randomWeights(weightsLayerTwo);
}