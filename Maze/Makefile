TARGET = mazeGameFinal.o
CPPFILES = mazegenfinal.cpp mazegamefinal.cpp DFS.cpp
HEADERFILES = mazeGame.h DFS.h

$(TARGET): $(CPPFILES) $(HEADERFILES)
	g++ $^ -o $@ -lncurses

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o

.PHONY: run clean