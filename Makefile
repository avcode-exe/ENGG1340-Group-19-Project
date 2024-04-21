TARGET = mazeGameFinal
CPPFILES = Maze/mazegenfinal.cpp main.cpp Maze/DFS.cpp Minesweeper/minesweeper.cpp
HEADERFILES = Maze/mazeGame.h Maze/DFS.h Minesweeper/minewseeper.h Minesweeper/colors.h Minesweeper/ms_config.h

$(TARGET): $(CPPFILES) $(HEADERFILES)
	g++ $^ -o $@ -lncurses

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean