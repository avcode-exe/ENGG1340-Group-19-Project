/**
 * @file maze generator.cpp
 * @brief This file contains the implementation of a maze generator using recursive randomized Prim's Algorithm.
 */

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <fstream>

using namespace std;

#define SIZE 55 // Update the size of the maze here
#define WALL 1
#define PATH 0

/**
 * @class Maze
 * @brief Represents a maze and provides methods for generating and printing the maze.
 */
class Maze {
  public:
    int startX; /**< The x-coordinate of the starting point of the maze */
    int startY; /**< The y-coordinate of the starting point of the maze */
    int maze[SIZE][SIZE]; /**< The maze grid */
    vector<vector<int>> directions = { {0, -2}, {2, 0}, {0, 2}, {-2, 0} }; /**< The possible directions to move in the maze */
    vector<vector<int>> potentialFrontier; /**< The list of potential frontier cells */

    /**
     * @brief Constructs a Maze object and initializes all cells in the maze to be walls.
     */
    Maze() : startX(1), startY(1){
      for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
          maze[y][x] = WALL;
        }
      }
    }

    /**
     * @brief Checks if a cell is a duplicate in the list of potential frontiers.
     * @param x The x-coordinate of the cell
     * @param y The y-coordinate of the cell
     * @return True if the cell is not a duplicate, false otherwise
     */
    bool checkduplicate(int x, int y) {
      for (const auto& vec : potentialFrontier) {
        if (vec[2] == x && vec[3] == y) {
          return false;
        }
      }
      return true;
    }

    /**
     * @brief Generates the maze using recursive randomized Prim's Algorithm.
     * @param x The x-coordinate of the current cell
     * @param y The y-coordinate of the current cell
     * @brief Steps:
     * 1. Select (x, y) to be the starting point
     * 2. Find all possible frontiers
     * 3. Randomly select a frontier
     * 4. Carve a path to the frontier
     * 5. Repeat steps 2-4 until there are no more frontiers
     * More info at https://en.wikipedia.org/wiki/Maze_generation_algorithm#Iterative_randomized_Prim's_algorithm_(without_stack,_without_sets)
     */
    void generateMaze(int x, int y) {
      // Selected (x, y) to be the starting point (step 1)
      maze[x][y] = PATH;

      // Find all possible frontiers (step 2)
      for (vector<int> direction : directions) {
        int nextX = x + direction[0];
        int nextY = y + direction[1];
        if (nextX > 0 && nextX < SIZE && nextY > 0 && nextY < SIZE && maze[nextX][nextY] == WALL && checkduplicate(nextX, nextY)) {
          potentialFrontier.push_back({x, y, nextX, nextY});
        }
      }

      // Remove duplicates
      sort(potentialFrontier.begin(), potentialFrontier.end());
      potentialFrontier.erase(unique(potentialFrontier.begin(), potentialFrontier.end()), potentialFrontier.end());

      // Step 3 to 6
      while (!potentialFrontier.empty()) {
        int randomIndex = rand() % potentialFrontier.size();
        vector<int> randomFrontier = potentialFrontier[randomIndex];
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

    bool noMonsterZone[SIZE][SIZE] = {false};


    void markNoMonsterZone(int cx, int cy) {
      for (int dx = -2; dx <= 2; ++dx) {
        for (int dy = -2; dy <= 2; ++dy) {
          int nx = cx + dx;
          int ny = cy + dy;
          if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
            noMonsterZone[ny][nx] = true;
          }
        }
      }
    }
    

      /**
   * @brief Places monsters in dead ends near the entrance of the maze.
   * @param density The density of monsters to be placed (0.0 to 1.0).
   */
void placeMonsters(float density) {
  for (int y = 1; y < SIZE - 1; y++) {
    for (int x = 1; x < SIZE - 1; x++) {
      if (maze[y][x] == PATH && isDeadEnd(x, y) && !noMonsterZone[y][x]) { // Check if the cell is not in a no-monster zone
        float chance = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        if (chance < density) {
          maze[y][x] = 'M'; // Place monster
        }
      }
    }
  }
}
    /**
   * @brief Checks if the cell at the given coordinates is a dead end.
   * @param x The x-coordinate of the cell
   * @param y The y-coordinate of the cell
   * @return True if the cell is a dead end, false otherwise
   */
bool isDeadEnd(int x, int y) {
  if (maze[y][x] == PATH) {
    int paths = 0;
    for (const auto& direction : directions) {
      int dx = direction[0];
      int dy = direction[1];
      if (x + dx >= 0 && x + dx < SIZE && y + dy >= 0 && y + dy < SIZE) {
        if (maze[y + dy][x + dx] == PATH) {
          paths++;
        }
      }
    }
    // A dead end will only have one adjacent path
    return paths == 1;
  }
  return false;
}
void placeCheckpoints() {
  // Function to check if a cell is a path and not a wall
  auto isPath = [this](int x, int y) -> bool {
    return maze[y][x] == PATH;
  };

  // Helper function to place a checkpoint if the position is not a wall
auto tryPlacingCheckpoint = [this, &isPath](int x, int y) {
  if (isPath(x, y)) {
    maze[y][x] = 'C';
    markNoMonsterZone(x, y); // Call this function whenever a checkpoint is placed
  } else {
    // Find the nearest path cell in the vicinity of the intended position
    for (int dx = -1; dx <= 1; ++dx) {
      for (int dy = -1; dy <= 1; ++dy) {
        int nx = x + dx;
        int ny = y + dy;
        if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && isPath(nx, ny)) {
          maze[ny][nx] = 'C';
          markNoMonsterZone(nx, ny); // Mark the no-monster zone for this checkpoint
          return; // Stop after placing one checkpoint
        }
      }
    }
  }
};


  // Define the six positions for the checkpoints. Adjust as necessary for exact placement.
  int middleX = SIZE / 2;
  int middleY = SIZE / 2;
  int offsetX = SIZE / 4; // Adjust offset as needed
  int offsetY = SIZE / 4; // Adjust offset as needed

  // Top-left
  tryPlacingCheckpoint(offsetX, offsetY);
  // Top-right
  tryPlacingCheckpoint(SIZE - offsetX - 1, offsetY);
  // Middle-left
  tryPlacingCheckpoint(offsetX, middleY);
  // Middle-right
  tryPlacingCheckpoint(SIZE - offsetX - 1, middleY);
  // Bottom-left
  tryPlacingCheckpoint(offsetX, SIZE - offsetY - 1);
  // Bottom-right
  tryPlacingCheckpoint(SIZE - offsetX - 1, SIZE - offsetY - 1);
}


    /**
     * @brief Prints the maze.
     */
  void printMaze() {
    for (int y = 0; y < SIZE; y++) {
      for (int x = 0; x < SIZE; x++) {
        if (maze[y][x] == 'C') { // Check for checkpoint and print 'C'
          cout << "C";
        } else if (maze[y][x] == 'M') { // Check for monster and print 'M'
          cout << "M";
        } else if (x == 1 && y == 0 || x == SIZE - 2 && y == SIZE - 1) {
          cout << " ";
        } else {
          cout << (maze[y][x] == WALL ? "▓" : " ");  // "▓"
        }
      }
      cout << endl;
    }
  }

/**
 * @brief Saves the maze to a file.
 */

void saveMaze() {
  ofstream file("maze.txt");
  if (file.is_open()) {
    for (int y = 0; y < SIZE; y++) {
      for (int x = 0; x < SIZE; x++) {
        if (maze[y][x] == 'C') { // Check for checkpoint and print 'C'
          file << "C";
        } else if (maze[y][x] == 'M') { // Check for monster and print 'M'
          file << "M";
        } else if (x == 1 && y == 0 || x == SIZE - 2 && y == SIZE - 1) {
          file << " ";
        } else {
          file << (maze[y][x] == WALL ? "#" : " "); // "#" for wall and " " for path
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
  // Initialize random number generator
  srand((unsigned) time(NULL));

  // Create a Maze class
  Maze maze;

  // Generating a maze
  cout << "Generating maze..." << endl;
  maze.generateMaze(maze.startX, maze.startY);
  cout << "Maze generated!" << endl;

  // Place checkpoints before placing monsters
  maze.placeCheckpoints();

  // Now place monsters with a certain density away from checkpoints
  float monsterDensity = 0.2f; // Adjust density as needed
  maze.placeMonsters(monsterDensity); // Call placeMonsters after checkpoints are placed

  // Print maze
  maze.printMaze();

  // Save maze
  maze.saveMaze();
  return 0;
}