#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Cell {
    int row;
    int col;
    Cell* next;
};

/**
 * Performs a depth-first search (DFS) on a maze to find a path from a given starting position to a goal position.
 * 
 * @param maze The maze represented as a 2D vector of characters.
 * @param row The current row position in the maze.
 * @param col The current column position in the maze.
 * @param path A list of cells representing the path from the starting position to the goal position.
 * @param goalRow The row position of the goal in the maze.
 * @param goalCol The column position of the goal in the maze.
 * @return True if a path from the starting position to the goal position is found, false otherwise.
 */
bool dfs(vector<vector<char>>& maze, int row, int col, Cell*& path, int goalRow, int goalCol) {
    if (row < 0 || row >= maze.size() || col < 0 || col >= maze[0].size() || maze[row][col] == '#') {
        return false;
    }

    if (row == goalRow && col == goalCol) {
        path = new Cell{row, col, path};
        return true;
    }

    maze[row][col] = '#';

    if (dfs(maze, row - 1, col, path, goalRow, goalCol) || dfs(maze, row + 1, col, path, goalRow, goalCol) ||
        dfs(maze, row, col - 1, path, goalRow, goalCol) || dfs(maze, row, col + 1, path, goalRow, goalCol)) {
        path = new Cell{row, col, path};
        return true;
    }

    return false;
}

/**
 * @brief The main function reads a maze from a file, performs a depth-first search (DFS) to find a path from the start to the goal, and prints the maze with the path marked.
 * 
 * @return int Returns 0 if the program executed successfully.
 */
int main() {
    ifstream file("maze.txt");
    if (!file) {
        cout << "Failed to open the maze file." << endl;
        return 1;
    }

    vector<vector<char>> maze;
    string line;
    while (getline(file, line)) {
        maze.push_back(vector<char>(line.begin(), line.end()));
    }

    int startRow = 0;
    int startCol = 1;
    int goalRow = maze.size() - 1;
    int goalCol = maze[0].size() - 2;

    Cell* path = nullptr;
    vector<vector<char>> mazeCopy = maze;
    bool foundPath = dfs(mazeCopy, startRow, startCol, path, goalRow, goalCol);

    if (foundPath) {
        cout << "Path found:" << endl;
    } else {
        cout << "No path found." << endl;
    }

    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            bool found = false;
            for (Cell* it = path; it != nullptr; it = it->next) {
                if (i == it->row && j == it->col) {
                    cout << '~' << ' ';
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << (maze[i][j] == '#' ? "▓▓" : "  ");
            }
        }
        cout << endl;
    }

    while (path != nullptr) {
        Cell* next = path->next;
        delete path;
        path = next;
    }

    return 0;
}
