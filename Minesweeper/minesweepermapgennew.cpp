#include "ms_config.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

void minefieldgen(int size, int mines, char cord[][SIZE]);
int randcord(int size);
bool checkismine(int x, int y,int size,char cord[][SIZE]);
int countmine(int x, int y, char cord[][SIZE]);

int main() {
	srand(time(NULL));
	char cord[SIZE][SIZE];

	minefieldgen(SIZE, MINES, cord);
}

//Generate a random number for coordinates
int randcord(int size) {
	return rand() % size;
}

//Check where the mine is
bool checkismine(int x, int y,int size, char cord[][SIZE]) {
	if (x<0 || x>size-1 || y<0 || y>size-1) 
		return false;
	if (cord[x][y] == 'X')
		return true;
	return false;
}


//Count the number of mines 
int countmine(int x, int y, int size, char cord[][SIZE]) {
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

//Generate the mine field 
void minefieldgen(int size, int mines, char cord[][SIZE]) {
	for (int i=0; i<size;i++) {
		for (int j=0; j<size; j++) {
			cord[i][j] = ' ';
		}
	}
	
	for (int m=0; m<mines; m++) {
		int x = randcord(SIZE);
		int y = randcord(SIZE);

		if (cord[x][y] == ' ') { 
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
	fout.open("minefield.txt");
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
