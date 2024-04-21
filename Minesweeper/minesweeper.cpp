#include "ms_config.h"
#include "colors.h"

#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

void loadMinefield(char cord[][SIZE]) {
    ifstream fin;
    noskipws(fin);
    fin.open("minefield.txt");

//    if (!fin) {
//        cerr << "Error opening minefield.txt" << endl;
//        exit(1);
//    }

    char newline;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> cord[i][j];
        }
        fin >> newline;
    }

    fin.close();
}

void printMinefield(char cord[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            setColor(cord[i][j]);
            cout << cord[i][j] << " ";
            resetColor();
        }
        cout << endl;
    }
}

void initGameBoard(char cord[][SIZE]) {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            cord[r][c] = '#';
        }
    }
}

bool checkIfRevealed(char cord[][SIZE], int row, int col) {
    if (cord[row][col] == '#' || cord[row][col] == 'f') {
        return false;
    }
    return true;
}

void revealPos(char cord[][SIZE], char gameBoard[][SIZE], int row, int col) {
    gameBoard[row][col] = cord[row][col];
}

bool checkIfMineFound(char cord[][SIZE], int row, int col) {
    if (cord[row][col] == 'X') {
        return true;
    }
    return false;
}

void placeFlag(char cord[][SIZE], int row, int col) {
    cord[row][col] = 'f';
}

bool checkIfGameWin(char cord[][SIZE]) {
    bool gameWin = true;
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (cord[r][c] == '#') {
                gameWin = false;
            }
        }
    }

    return gameWin;
}

void revealCells(char cord[][SIZE], char gameBoard[][SIZE], int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return;
    }

    if (cord[row][col] == '0' && gameBoard[row][col] == '#') {
        gameBoard[row][col] = cord[row][col];
        revealCells(cord, gameBoard, row - 1, col);
        revealCells(cord, gameBoard, row + 1, col);
        revealCells(cord, gameBoard, row, col - 1);
        revealCells(cord, gameBoard, row, col + 1);
    }
}

int minewseepeMain() {
    char cord[SIZE][SIZE];
    loadMinefield(cord);

    char gameBoard[SIZE][SIZE];
    initGameBoard(gameBoard);

    string str_in, errorMsg;
    int row_in, col_in;
    bool flagMode;

    while (!checkIfGameWin(gameBoard)) {
        system("clear");
        flagMode = false;

        printMinefield(gameBoard);
        cout << endl;

        if (errorMsg != "") {
            cout << "\033[91m" << errorMsg << "\033[0m" << endl;
        }
        cout << "Enter coordinates: ";
        getline(cin, str_in);
        errorMsg = "";

        istringstream iss(str_in);
        if (str_in.substr(0, str_in.find(" ")) == "f") {
            flagMode = true;

            char f_flag;
            iss >> f_flag;
        }

        iss >> row_in >> col_in;
        char extraArgs;
        if (iss >> extraArgs) {
            errorMsg = "Too many arguments. Please enter again.";
            continue;
        }

        if (flagMode) {
            if (checkIfRevealed(gameBoard, row_in, col_in)) {
                errorMsg = "Unable to flag revealed tiles. Please choose another one.";
                continue;
            }
            placeFlag(gameBoard, row_in, col_in);
        } else {
            if (checkIfRevealed(gameBoard, row_in, col_in)) {
                errorMsg = "Tile was already revealed. Please choose another one.";
                continue;
            }
            revealPos(cord, gameBoard, row_in, col_in);

            if (checkIfMineFound(cord, row_in, col_in)) {
                system("clear");
                printMinefield(gameBoard);
                cout << endl;

                cout << "\033[91m" << "GAME OVER!" << "\033[0m" << endl;
                return 1;
            }
        }
    }

    cout << "GAME CLEARED!" << endl;
    return 0;
}
