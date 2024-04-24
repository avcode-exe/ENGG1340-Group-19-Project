#include "minewseepergen.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
// Load
void loadMinefield(char cord[][MSIZE]) {
  string minefield_stream;

  ifstream fin;
  noskipws(fin);
  fin.open("minefield.txt");

  if (fin.fail()) {
    cout << "error opening minefield.txt" << endl;
    exit(1);
  };

  char newline;
  for (int i = 0; i < MSIZE; i++) {
    for (int j = 0; j < MSIZE; j++) {
      fin >> cord[i][j];
    }
    fin >> newline;
  };

  fin.close();
}
void display(char cord[][MSIZE], int posX, int posY, bool flagMode,
             string message) {
  move(0, 0);
  for (int i = 0; i < MSIZE; i++) {
    for (int j = 0; j < MSIZE; j++) {
      if (cord[i][j] == 'X') {
        attron(COLOR_PAIR(3));
        addch(cord[i][j]);
        attroff(COLOR_PAIR(3));
      } else if (cord[i][j] == 'F') {
        attron(COLOR_PAIR(4));
        addch(cord[i][j]);
        attroff(COLOR_PAIR(4));
      } else if (i == posY && j == posX) {
        attron(COLOR_PAIR(2));
        addch(cord[i][j]);
        attroff(COLOR_PAIR(2));
      } else {
        attron(COLOR_PAIR(1));
        addch(cord[i][j]);
        attroff(COLOR_PAIR(1));
      }
    };
    addch('\n');
  };
  printw("Current coordinates: %d %d %s", posX, posY,
         flagMode ? "(flag ON)" : "(flag OFF)");
  printw("\n");
  if (message == "")
    printw("Use spacebar to select tile, 'f' to flag");
  else {
    printw("%s", message.c_str());
  }
  refresh();
}

void initGameBoard(char cord[][MSIZE]) {
  for (int r = 0; r < MSIZE; r++) {
    for (int c = 0; c < MSIZE; c++) {
      cord[r][c] = '#';
    }
  }
}

bool checkIfRevealed(char cord[][MSIZE], int row, int col) {
  if (cord[row][col] == '#' || cord[row][col] == 'F') {
    return false;
  };
  return true;
}

bool revealPos(char cord[][MSIZE], char gameBoard[][MSIZE], int row, int col,
               vector<vector<int>> &visited) {
  // getch();
  if (std::find(visited.begin(), visited.end(), vector<int>{row, col}) ==
      visited.end()) {
    visited.push_back(vector<int>{row, col});
    gameBoard[row][col] = cord[row][col];
    if (cord[row][col] != ' ') {
      // printw("rejected");
      return false;
    }
    // clear();
    for (vector<int> spread : vector<vector<int>>{{row - 1, col - 1},
                                                  {row - 1, col},
                                                  {row - 1, col + 1},
                                                  {row, col - 1},
                                                  {row, col + 1},
                                                  {row + 1, col - 1},
                                                  {row + 1, col},
                                                  {row + 1, col + 1}}) {
      if (spread[0] >= 0 && spread[0] < MSIZE && spread[1] >= 0 &&
          spread[1] < MSIZE) {
        // printw("\nrecuring %d %d (from %d %d)", spread[0], spread[1], row,
        // col); refresh();
        revealPos(cord, gameBoard, spread[0], spread[1], visited);
      }
    }
  }
  // printw("skipped");
  return false;
}

bool checkIfMineFound(char cord[][MSIZE], int row, int col) {
  if (cord[row][col] == 'X') {
    return true;
  };
  return false;
}

void placeFlag(char cord[][MSIZE], int row, int col) {
  if (cord[row][col] == '#') {
    cord[row][col] = 'F';
    return;
  }
  if (cord[row][col] == 'F') {
    cord[row][col] = '#';
    return;
  }
}
bool checkIfGameWin(char cord[][MSIZE]) {
  bool gameWin = true;
  for (int r = 0; r < MSIZE; r++) {
    for (int c = 0; c < MSIZE; c++) {
      if (cord[r][c] == '#') {
        gameWin = false;
      }
    }
  };

  return gameWin;
}

int minesweeper() {
  minewsweepergenmain();
  char usrInput{};
  int posX = 0;
  int posY = 0;
  char mf[MSIZE][MSIZE];
  loadMinefield(mf);

  char gameBoard[MSIZE][MSIZE];
  initGameBoard(gameBoard);

  bool gameLose = false;
  string str_in, errorMsg;
  int row_in, col_in;
  bool flagMode;
  bool act;
  while (!checkIfGameWin(gameBoard)) {
    flagMode = false;
    act = false;
    clear();
    refresh();
    while (!act) {
      // printMinefield(gameBoard);
      display(gameBoard, posX, posY, flagMode, errorMsg);

      if (errorMsg != "") {
        // cout << "\033[91m" << errorMsg << "\033[0m" << endl;
      };
      usrInput = getch();
      switch (usrInput) {
      case 'w':
        if (posY > 0)
          posY--;
        break;
      case 's':
        if (posY + 1 < MSIZE)
          posY++;
        break;
      case 'a':
        if (posX > 0)
          posX--;
        break;
      case 'd':
        if (posX + 1 < MSIZE)
          posX++;
        break;
      case ' ':
        col_in = posX;
        row_in = posY;
        act = true;
        break;
      case 'f':
        flagMode = !flagMode;
        break;
#ifdef DEBUG
      case 'y':
        return 0;
#endif
      }
    }
#if 0
#endif
    if (flagMode) {
      if (checkIfRevealed(gameBoard, row_in, col_in)) {
        errorMsg = "Unable to flag revealed tiles. Please choose another one.";
        continue;
      };
      placeFlag(gameBoard, row_in, col_in);
    } else {
      if (checkIfRevealed(gameBoard, row_in, col_in)) {
        errorMsg = "Tile was already revealed. Please choose another one.";
        continue;
      };
      vector<vector<int>> visited{};
      revealPos(mf, gameBoard, row_in, col_in, visited);

      if (checkIfMineFound(mf, row_in, col_in)) {
        gameLose == true;
        display(gameBoard, posX, posY, flagMode, "GAME OVER!\n You Lose!");
        return -1;
      }
    }
  };

  display(gameBoard, posX, posY, flagMode,
          "Cleared!");
  return 0;
}
