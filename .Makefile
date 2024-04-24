#TARGET_MAZE: mazeGameFinal
#TARGET_MS: minesweeper
MAZE_PATH = ./Maze/
MS_PATH = ./Minesweeper/

all: minesweeper maze

minesweeper: $(MS_PATH)Makefile
	cd $(MS_PATH) && $(MAKE)
maze: $(MAZE_PATH)Makefile
	cd $(MAZE_PATH) && $(MAKE)


clean: clean_ms clean_maze

clean_ms: $(MS_PATH)Makefile
	cd $(MS_PATH) && $(MAKE) clean

clean_maze: $(MAZE_PATH)Makefile
	cd $(MAZE_PATH) && $(MAKE) clean

.PHONY: minesweeper maze clean
