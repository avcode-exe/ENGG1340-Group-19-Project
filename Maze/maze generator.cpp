// Import required libraries
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <fstream>

using namespace std;

// Define constants
#define SIZE 55
#define WALL 1
#define PATH 0

// Maze Class
class Maze {
  public:
  	// Define required variables for the maze
    int startX;
    int startY;
    int maze[SIZE][SIZE];
    vector<vector<int>> directions = { {0, -2}, {2, 0}, {0, 2}, {-2, 0} };
    vector<vector<int>> potentialFrontier;

		// Maze constructor
		// Initialized all cells in a maze to be wall
    Maze() : startX(1), startY(1){
      for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
          maze[y][x] = WALL;
        }
      }
    }

		// Assistive functions for generateMaze()
    bool checkduplicate(int x, int y) {
      for (const auto& vec : potentialFrontier) {
        if (vec[2] == x && vec[3] == y) {
          return false;
        }
      }
      return true;
    }

		// Using recursive randomized Prim's Algorithm for generating mazes
		// Prim's Algorithm is as follows
		//  1. Initialize the maze with walls (did in the constructor for Maze class)
		//  2. Randomly select a cell to be the path and starting point of the algorithm
		//  3. Find all possible frontiers (vertical and horizontal adjacent cells of the path) which has the chance of being the path
		//  4. Randomly select one of the frontiers and make it a path and the middle cell to be a path
		//  5. The remove the selected cell from the list of possible frontiers
		//  6. Repeat step 3 to 5 until the list of possible frontiers is empty
		// Reference link: https://en.wikipedia.org/wiki/Maze_generation_algorithm#Iterative_randomized_Prim's_algorithm_(without_stack,_without_sets)

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

    // Print the Maze
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

		// Save the maze (Current the wall is "#", still under construction for better maze appearance)
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
	// Initialize random number generator
  srand((unsigned) time(NULL));

  // Create a Maze class
  Maze maze;

  // Generating a maze
  cout << "Generating maze..." << endl;
  maze.generateMaze(maze.startX, maze.startY);
  cout << "Maze generated!" << endl;

  // Print maze
  maze.printMaze();

  // Save maze
  maze.saveMaze();
  return 0;
}
