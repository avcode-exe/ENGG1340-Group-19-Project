#include "ms_config.h"

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
void loadMinefield(char cord[][SIZE]) {
  string minefield_stream;

  ifstream fin;
  noskipws(fin);
  fin.open("minefield.txt");

  if (fin.fail()) {
    cout << "error opening minefield.txt" << endl;
    exit(1);
  };

  char newline;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      fin >> cord[i][j];
    }
    fin >> newline;
  };

  fin.close();
}
void display(char cord[][SIZE], int posX, int posY, bool flagMode) {
  clear();
  move(0, 0);
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (cord[i][j] == 'X') {
        attron(COLOR_PAIR(3));
        addch(cord[i][j]);
        attroff(COLOR_PAIR(3));
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
         flagMode ? "(flagged)" : "");
  refresh();
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
  };
  return true;
}

bool revealPos(char cord[][SIZE], char gameBoard[][SIZE], int row, int col,
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
      if (spread[0] >= 0 && spread[0] < SIZE && spread[1] >= 0 &&
          spread[1] < SIZE) {
        // printw("\nrecuring %d %d (from %d %d)", spread[0], spread[1], row,
        // col); refresh();
        revealPos(cord, gameBoard, spread[0], spread[1], visited);
      }
    }
  }
  // printw("skipped");
  return false;
}

bool checkIfMineFound(char cord[][SIZE], int row, int col) {
  if (cord[row][col] == 'X') {
    return true;
  };
  return false;
}

void placeFlag(char cord[][SIZE], int row, int col) { cord[row][col] = 'f'; }

bool checkIfGameWin(char cord[][SIZE]) {
  bool gameWin = true;
  for (int r = 0; r < SIZE; r++) {
    for (int c = 0; c < SIZE; c++) {
      if (cord[r][c] == '#') {
        gameWin = false;
      }
    }
  };

  return gameWin;
}

int main() {
  initscr();
  cbreak();
  noecho();
  start_color();

  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  char usrInput{};
  int posX = 0;
  int posY = 0;
  char mf[SIZE][SIZE];
  loadMinefield(mf);

  char gameBoard[SIZE][SIZE];
  initGameBoard(gameBoard);

  bool gameLose = false;
  string str_in, errorMsg;
  int row_in, col_in;
  bool flagMode;
  bool act;
  while (!checkIfGameWin(gameBoard)) {
    system("clear");
    flagMode = false;
    act = false;
    while (!act) {
      // printMinefield(gameBoard);
      display(gameBoard, posX, posY, flagMode);

      if (errorMsg != "") {
        cout << "\033[91m" << errorMsg << "\033[0m" << endl;
      };
      usrInput = getch();
      switch (usrInput) {
      case 'w':
        if (posY > 0)
          posY--;
        break;
      case 's':
        if (posY + 1 < SIZE)
          posY++;
        break;
      case 'a':
        if (posX > 0)
          posX--;
        break;
      case 'd':
        if (posX + 1 < SIZE)
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
        system("clear");
        display(gameBoard, posX, posY, flagMode);
        cout << endl;

        cout << "\033[91m"
             << "GAME OVER!"
             << "\033[0m" << endl;
        return 0;
      }
    }
  };

  cout << "GAME CLEARED!" << endl;
  return 0;
}
