#pragma once

#include <list>
using namespace std;

/**
 * @struct Cell
 * @brief Represents a cell in the maze.
 * 
 * The Cell struct stores the row and column coordinates of a cell in the maze.
 */
struct Cell {
    int row; /**< The row coordinate of the cell. */
    int col; /**< The column coordinate of the cell. */
};
struct Cell {
    int row;
    int col;
};

list<Cell> path;