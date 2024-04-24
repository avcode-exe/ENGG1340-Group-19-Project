# #TARGET_MAZE: mazeGameFinal
# #TARGET_MS: minesweeper
# MAZE_PATH = ./Maze/
# MS_PATH = ./Minesweeper/

# all: minesweeper maze

# minesweeper: $(MS_PATH)Makefile
# 	cd $(MS_PATH) && $(MAKE)
# maze: $(MAZE_PATH)Makefile
# 	cd $(MAZE_PATH) && $(MAKE)


# clean: clean_ms clean_maze

# clean_ms: $(MS_PATH)Makefile
# 	cd $(MS_PATH) && $(MAKE) clean

# clean_maze: $(MAZE_PATH)Makefile
# 	cd $(MAZE_PATH) && $(MAKE) clean

# .PHONY: minesweeper maze clean

# Define compiler and flags
CXX = g++
CPPFLAGS = -pedantic-errors -Werror -std=c++11
LDFLAGS = -lncurses

# Define paths
MAZE_SRC = Maze/main.cpp Maze/DFS.cpp Maze/mazegenfinal.cpp
MS_SRC = Minesweeper/minesweeper.cpp Minesweeper/minesweepermapgen.cpp
INCLUDES = -IMaze -IMinesweeper

# Define the target
TARGET = mazeGame

# Define all source files
SRC = $(MAZE_SRC) $(MS_SRC)

# Define object files from source files
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to link the program
$(TARGET): $(OBJ)
	$(CXX) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

# Clean target
clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean