#include <iostream>
#include <cstdlib>
#include <ctime>
#define SIZE 15
using namespace std;

const int size=15;
const int mines=20;

void minefieldgen(int size, int mines, char cord[][SIZE]);
int randcord(int size);
bool checkismine(int x, int y,int size,char cord[][SIZE]);
int countmine(int x, int y, char cord[][SIZE]);

int main() {
	srand(time(NULL));
	char cord[SIZE][SIZE];
	
	minefieldgen(size, mines, cord);
}

int randcord(int size) {
	return rand() % size;
}


bool checkismine(int x, int y,int size, char cord[][SIZE]) {
	if (x<0 || x>size-1 || y<0 || y>size-1) 
		return false;
	if (cord[x][y] == 'X')
		return true;
	return false;
}



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


void minefieldgen(int size, int mines, char cord[][SIZE]) {
	for (int i=0; i<size;i++) {
		for (int j=0; j<size; j++) {
			cord[i][j] = ' ';
		}
	}
	
	for (int m=0; m<mines+1; m++) {
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



	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			cout << cord[i][j];
		}
		cout << endl;
	}


}
