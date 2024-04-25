#include "minewseepergen.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

void minefieldgen(int size, int mines, char cord[][MSIZE]);
int randcord(int size);
bool checkismine(int x, int y,int size,char cord[][MSIZE]);
int countmine(int x, int y, char cord[][MSIZE]);

void minewsweepergenmain() {
	srand(time(NULL));
	char cord[MSIZE][MSIZE];

	minefieldgen(MSIZE, MINES, cord);
}

int randcord(int size) {
	return rand() % size;
}


bool checkismine(int x, int y,int size, char cord[][MSIZE]) {
	if (x<0 || x>size-1 || y<0 || y>size-1) 
		return false;
	if (cord[x][y] == 'X')
		return true;
	return false;
}



int countmine(int x, int y, int size, char cord[][MSIZE]) {
	int mines =0;
	
	if (checkismine(x-1,y,size,cord))
		mines += 1;
	if (checkismine(x+1,y,size,cord))
		mines += 1;
	if (checkismine(x,y-1,size,cord))
		mines += 1;
	if (checkismine(x,y+1,size,cord))
		mines += 1;
	if (checkismine(x-1,y-1,size,cord))
		mines += 1;
	if (checkismine(x-1,y+1,size,cord))
		mines += 1;
	if (checkismine(x+1,y-1,size,cord))
		mines += 1;
	if (checkismine(x+1,y+1,size,cord))
		mines += 1;

	return mines;
}


void minefieldgen(int size, int mines, char cord[][MSIZE]) {
	for (int i=0; i<size;i++) {
		for (int j=0; j<size; j++) {
			cord[i][j] = ' ';
		}
	}
	
	for (int m=0; m<mines; m++) {
		int x = randcord(MSIZE);
		int y = randcord(MSIZE);

		if (cord[x][y] == ' ' && x != 0 && y != 0) {
			cord[x][y] = 'X';
		}
		else
			m = m-1;
	}

	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			if (cord[i][j] != 'X'){
				int nummine = countmine(i,j,size,cord);
				if (nummine >0)
					cord[i][j] = '0' + nummine;
			}
		}
	}

	ofstream fout;
	noskipws(fout);
	fout.open(".gameConfig/minefield.txt");
	if (fout.fail()) {
		cout << "error opening minefield.txt" << endl;
		exit(1);
	};

	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			fout << cord[i][j];
		}
		fout << endl;
	};

	fout.close();

}
