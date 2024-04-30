# ENGG1340-Group-19-Project

HKU ENGG1340/COMP2113 (2023 - 2024)
Group 19 Project

## Groupmates

- Liu Hong Yuan Tom (3036262135)
- Wong Yiu Wing Wilson (3036262032)
- Ho Ho Cheung Sky (3036136934)
- Chan Ho Yin David (3036035075)
- Chan Pak Yin Perry (3036140284)

## About Our Project

Our project consists of a maze game and a minesweeper game.

To begin with, the player has to complete the maze while avoiding monsters nearby.
However, if the player gets hit by the monster, the player will be sent to a game of minesweeper.
If the player loses during the minesweeper game, a health point will be deducted and the player returns to the maze game.

The goal is to reach the exit of the maze before the player loses all health points.

## List of Features

- A maze generated using recursive randomized Prim's algorithm
	- A frontier is randomly selected from the list of potential frontiers using `<random>`. The algorithm then removes the wall between the original coordinates and the selected frontier and thus carve a path.
	- STL vectors are used to initialize and store frontiers and their possible directions. It is also used for the `potentialFrontiers` array, a list of frontiers the algorithm can choose from randomly.
	- Dynamic pointers are used to instantiate objects of struct Cell for the Depth-First Search (DFS) algorithm, which finds the path from a starting position to the goal position in the maze.
	- The maze generated is also saved to a text file using `<fstream>`. The content of the maze in the text file is then loaded to `mazeGame.cpp` and printed on the screen.
	- Different source code and header files are compiled separately in a Makefile.

- There are monsters moving in various locations of the maze and checkpoints generated in random locations
	- MT19937 is used for the random generation of a random device, which is then used to shuffle the list of potential monster positions.
	- STL vectors and pairs are used to store a list of potential monster positions, with the first value in the pair container being the x-coordinate and the second value being the y-coordinate.
	- Monsters are represented with the character 'M' and are saved to the text file along with the maze.
	- Different source code and header files are compiled separately in a Makefile.

- A game of minesweeper commences when the player is hit by the monster
	- `rand()` from `<cstdlib>` is used to generate random coordinates for mines.
	- STL vectors are used to store a list of coordinates that have been visited by the player.
	- The minesweeper game board is saved in a text file using `<fstream>`, which is then loaded to `minesweeper.cpp` and printed on the screen.
	- Different source code and header files are compiled separately in a Makefile.

## List of non-standard C/C++ libraries

- ncurses

## Compilation and execution instructions

Download the repository as a zip file. Alternatively, you can also run this command to clone the repository to your local device:
```sh
git clone https://github.com/avcode-exe/ENGG1340-Group-19-Project.git
```

Navigate to the folder. To run the game, simply run `make run` to compile and execute the program.