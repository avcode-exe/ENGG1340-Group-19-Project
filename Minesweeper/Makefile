all: minesweepermapgen.o minesweeper.o minesweepermapgen minesweeper

minesweepermapgen: minesweepermapgen.o
	g++ -pedantic-errors -std=c++11 -o minesweepermapgen minesweepermapgen.o

minesweeper: minesweeper.o
	g++ -pedantic-errors -std=c++11 -o minesweeper minesweeper.o

minesweepermapgen.o: minesweepermapgen.cpp ms_config.h
	g++ -c minesweepermapgen.cpp

minesweeper.o: minesweeper.cpp ms_config.h colors.h
	g++ -c minesweeper.cpp

clean:
	rm minesweeper minesweepermapgen

run:
	./minesweepermapgen
	./minesweeper

reroll:
	./minesweepermapgen

.PHONY: clean run reroll
