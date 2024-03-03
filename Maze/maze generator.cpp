#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <fstream>

using namespace std;

#define SIZE 55
#define WALL 1
#define PATH 0

class Maze {
  public:
    int startX;
    int startY;
    int maze[SIZE][SIZE];
    vector<vector<int>> directions = { {0, -2}, {2, 0}, {0, 2}, {-2, 0} };
    vector<vector<int>> potentialFrontier;

    Maze() : startX(1), startY(1){
      for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
          maze[y][x] = WALL;
        }
      }
    }

    bool checkduplicate(int x, int y) {
      for (const auto& vec : potentialFrontier) {
        if (vec[2] == x && vec[3] == y) {
          return false;
        }
      }
      return true;
    }

    void generateMaze(int x, int y) {
      maze[x][y] = PATH;
      for (vector<int> direction : directions) {
        int nextX = x + direction[0];
        int nextY = y + direction[1];
        if (nextX > 0 && nextX < SIZE && nextY > 0 && nextY < SIZE && maze[nextX][nextY] == WALL && checkduplicate(nextX, nextY)) {
          potentialFrontier.push_back({x, y, nextX, nextY});
        }
      }

      sort(potentialFrontier.begin(), potentialFrontier.end());
      potentialFrontier.erase(unique(potentialFrontier.begin(), potentialFrontier.end()), potentialFrontier.end());

      while (!potentialFrontier.empty()) {
        // cout << "Potential frontier - ";
        // for (const auto& vec : potentialFrontier) {
        //   cout << "{";
        //   for (const auto& num : vec) {
        //     cout << num << ",";
        //   }
        //   cout << "} ";
        // }
        // cout << endl;
        // printMaze();
        int randomIndex = rand() % potentialFrontier.size();
        vector<int> randomFrontier = potentialFrontier[randomIndex];
        // cout << "Random frontier - {" << randomFrontier[2] << "," << randomFrontier[3] << "}" << endl;
        // cout << "x - " << randomFrontier[0] << " y - " << randomFrontier[1] << endl;
        potentialFrontier.erase(potentialFrontier.begin() + randomIndex);
        int frontierX = randomFrontier[2];
        int frontierY = randomFrontier[3];
        int wallX = (frontierX + randomFrontier[0]) / 2;
        int wallY = (frontierY + randomFrontier[1]) / 2;
        if (maze[wallX][wallY] == WALL) {
          maze[wallX][wallY] = PATH;
          maze[frontierX][frontierY] = PATH;
          generateMaze(frontierX, frontierY);
        }
      }
    }
    
    void printMaze() {
      for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
          if (x == 1 && y == 0) {
            cout << " ";
          } else if (x == SIZE - 2 && y == SIZE - 1) {
            cout << " ";
          } else {
            cout << (maze[y][x] == WALL ? "▓" : " ");
          }
        }
        cout << endl;
      }
    }

    void saveMaze() {
      ofstream file("maze.txt");
      if (file.is_open()) {
        for (int y = 0; y < SIZE; y++) {
          for (int x = 0; x < SIZE; x++) {
            if (x == 1 && y == 0) {
              file << " ";
            } else if (x == SIZE - 2 && y == SIZE - 1) {
              file << " ";
            } else {
              file << (maze[y][x] == WALL ? "#" : " ");
            }
          }
          file << "\n";
        }
        file.close();
      } else {
        cout << "Unable to open file";
      }
    }
};

int main() {
  srand((unsigned) time(NULL));
  Maze maze;
  cout << "Generating maze..." << endl;
  maze.generateMaze(maze.startX, maze.startY);
  cout << "Maze generated!" << endl;
  maze.printMaze();
  maze.saveMaze();
  return 0;
}