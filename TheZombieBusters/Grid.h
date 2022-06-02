#pragma once
#include "entity.h"
#include <iostream>
#include <ctime>

#define EMPTY 0
#define FULL 1

using std::cout;

struct gridCell {
	char Cell;
	int emptyFull;
	int derick;
	int chiconne;
};


class Grid
{
private:
	gridCell** grid;
	gridCell** showGrid;
	int H_Ammo;
	int H_LMK;
	int H_SMK;
	int H_LZ;
	int H_MZ;
	int H_SZ;
	int size;

public:
	Grid(int n) {

		srand(time(NULL));

		int i, j, totZombies, totMK;
		this->size = n;
		this->grid = (gridCell**)calloc(n, sizeof(gridCell*));
		for (i = 0; i < n; i++)
			this->grid[i] = (gridCell*)calloc(n, sizeof(gridCell));

		this->showGrid = (gridCell**)calloc(n, sizeof(gridCell*));
		for (i = 0; i < n; i++)
			this->showGrid[i] = (gridCell*)calloc(n, sizeof(gridCell));

		this->H_Ammo = 2 * ((n * n) / 25);
		totZombies = 2 * ((n * n) / 25);
		totMK = 3 * ((n * n) / 25);
		//initializing total amount of each type of zombie
		if (totZombies == 2) {
			this->H_LZ = 1;
			this->H_MZ = 1;
		}
		else {
			this->H_LZ = rand() % totZombies;
			this->H_MZ = rand() % (totZombies - this->H_LZ);
			this->H_SZ = totZombies - this->H_LZ - this->H_MZ;
		}
		//initializing total amount of each type of medicine kit
		this->H_LMK = rand() % totMK;
		this->H_SMK = totMK - this->H_LMK;
		//placing everything on the grid
		//cout << "\n" << H_LZ << " " << H_MZ << " " << H_SZ << " " << H_LMK << " " << H_SMK << " " << H_Ammo << "\n";
		this->placeEntities();

		for (i = 0; i < this->size; i++) {
			for (j = 0; j < this->size; j++) {
				if (grid[i][j].Cell == 'D') {
					this->showGrid[i][j].Cell = 'D';
					this->showGrid[i][j].emptyFull = FULL;
					this->showGrid[i][j].derick = 1;
				}
				else if (grid[i][j].Cell == 'C') {
					this->showGrid[i][j].Cell = 'C';
					this->showGrid[i][j].emptyFull = FULL;
					this->showGrid[i][j].chiconne = 1;
				}
				else {
					this->showGrid[i][j].Cell = 'x';
					this->showGrid[i][j].emptyFull = EMPTY;
					this->showGrid[i][j].derick = 0;
					this->showGrid[i][j].chiconne = 0;
				}
			}
		}
	}

	void placeEntities(void) {
		int i, j, t1, t2, done = 0;

		srand(time(NULL));

		for (i = 0; i < this->size; i++) {
			for (j = 0; j < this->size; j++) {
				this->grid[i][j].Cell = 'x';
				this->grid[i][j].emptyFull = EMPTY;
				this->grid[i][j].derick = 0;
				this->grid[i][j].chiconne = 0;
			}
		}

		while (done == 0) {
			t1 = rand() % size; t2 = rand() % size;
			if (this->grid[t1][t2].emptyFull == EMPTY) {
				this->grid[t1][t2].Cell = 'C';
				this->grid[t1][t2].emptyFull = FULL;
				this->grid[t1][t2].chiconne = 1;
				done = 1;
			}
		}

		done = 0;
		while (done == 0) {
			t1 = rand() % size; t2 = rand() % size;
			if (this->grid[t1][t2].emptyFull == EMPTY) {
				this->grid[t1][t2].Cell = 'D';
				this->grid[t1][t2].emptyFull = FULL;
				this->grid[t1][t2].derick = 1;
				done = 1;
			}
		}

		done = 0;
		for (i = 0; i < this->H_Ammo; i++) {
			while (done == 0) {
				t1 = rand() % size; t2 = rand() % size;
				if (this->grid[t1][t2].emptyFull == EMPTY) {
					this->grid[t1][t2].Cell = 'A';
					this->grid[t1][t2].emptyFull = FULL;
					done = 1;
				}
			}
			done = 0;
		}

		done = 0;
		for (i = 0; i < this->H_LMK; i++) {
			while (done == 0) {
				t1 = rand() % size; t2 = rand() % size;
				if (this->grid[t1][t2].emptyFull == EMPTY) {
					this->grid[t1][t2].Cell = '*';
					this->grid[t1][t2].emptyFull = FULL;
					done = 1;
				}
			}
			done = 0;
		}

		done = 0;
		for (i = 0; i < this->H_SMK; i++) {
			while (done == 0) {
				t1 = rand() % size; t2 = rand() % size;
				if (this->grid[t1][t2].emptyFull == EMPTY) {
					this->grid[t1][t2].Cell = '+';
					this->grid[t1][t2].emptyFull = FULL;
					done = 1;
				}
			}
			done = 0;
		}

		done = 0;
		for (i = 0; i < this->H_LZ; i++) {
			while (done == 0) {
				t1 = rand() % size; t2 = rand() % size;
				if (this->grid[t1][t2].emptyFull == EMPTY) {
					this->grid[t1][t2].Cell = 'L';
					this->grid[t1][t2].emptyFull = FULL;
					done = 1;
				}
			}
			done = 0;
		}

		done = 0;
		for (i = 0; i < this->H_MZ; i++) {
			while (done == 0) {
				t1 = rand() % size; t2 = rand() % size;
				if (this->grid[t1][t2].emptyFull == EMPTY) {
					this->grid[t1][t2].Cell = 'M';
					this->grid[t1][t2].emptyFull = FULL;
					done = 1;
				}
			}
			done = 0;
		}

		done = 0;
		for (i = 0; i < this->H_SZ; i++) {
			while (done == 0) {
				t1 = rand() % size; t2 = rand() % size;
				if (this->grid[t1][t2].emptyFull == EMPTY) {
					this->grid[t1][t2].Cell = 'S';
					this->grid[t1][t2].emptyFull = FULL;
					done = 1;
				}
			}
			done = 0;
		}

	}
	bool gameEnd (void) {
		int i, j;
		for (i = 0; i < this->size; i++) {
			for (j = 0; j < this->size; j++) {
				if (this->grid[i][j].Cell == 'L' || this->grid[i][j].Cell == 'M' || this->grid[i][j].Cell == 'S') {
						return false;
				}
			}
		}
		return true;
	}
	void printGrid(void) {         
		int i, j;
		cout << "  ";
		for (i = 0; i < this->size; i++) cout << i << " ";

		cout << "\n";

		for (i = 0; i < this->size; i++) {
			cout << i << " ";
			for (j = 0; j < this->size; j++) {
				cout << this->showGrid[i][j].Cell << " ";
			}
			cout << "\n";
		}
	}

	void printGrid2(void) {         
		int i, j;
		cout << "  ";
		for (i = 0; i < this->size; i++) cout << i << " ";

		cout << "\n";

		for (i = 0; i < this->size; i++) {
			cout << i << " ";
			for (j = 0; j < this->size; j++) {
				cout << this->grid[i][j].Cell << " ";
			}
			cout << "\n";
		}
	}

	void updateGrid(int i, int j, char zombie) {
		showGrid[i][j].Cell = zombie;
		showGrid[i][j].derick = 0;
		showGrid[i][j].chiconne = 0;
	}
	char getCoordinateRep(int x, int y) {
		return this->grid[x][y].Cell;
	}
	void setCoordinateRep(int x, int y, char ent) {
		this->grid[x][y].Cell = ent;
	}
	bool moveDerick(int i, int j) { //i,j here are the new coordinates of the warrior
		int iCur = 0, jCur = 0, x, y;

		for (x = 0; x < this->size; x++) {
			for (y = 0; y < this->size; y++) {
				if (this->grid[x][y].Cell == 'D') {
					iCur = x; jCur = y;
					break;
				}
			}
		}

		if (this->grid[i][j].derick == 1 || this->grid[i][j].Cell == 'C')
			return false;
		else {
			this->grid[i][j].Cell = 'D';
			this->grid[i][j].derick = 1;
			this->grid[i][j].emptyFull = FULL;
			this->showGrid[i][j].Cell = 'D';
			this->showGrid[i][j].derick = 1;
			this->showGrid[i][j].emptyFull = FULL;
		}

		this->grid[iCur][jCur].Cell = 'x';
		this->grid[iCur][jCur].emptyFull = EMPTY;
		this->showGrid[iCur][jCur].Cell = ' ';
		this->showGrid[iCur][jCur].emptyFull = EMPTY;

		return true;
	}

	bool moveChiconne(int i, int j) { //i,j here are the new coordinates of the warrior
		int iCur = 0, jCur = 0, x, y;

		for (x = 0; x < this->size; x++) {
			for (y = 0; y < this->size; y++) {
				if (this->grid[x][y].Cell == 'C') {
					iCur = x; jCur = y;
					break;
				}
			}
		}

		if (this->grid[i][j].chiconne == 1 || this->grid[i][j].Cell == 'D')
			return false;
		else {
			this->grid[i][j].Cell = 'C';
			this->grid[i][j].chiconne = 1;
			this->grid[i][j].emptyFull = FULL;
			this->showGrid[i][j].Cell = 'C';
			this->showGrid[i][j].chiconne = 1;
			this->showGrid[i][j].emptyFull = FULL;
		}

		this->grid[iCur][jCur].Cell = 'x';
		this->grid[iCur][jCur].emptyFull = EMPTY;
		this->showGrid[iCur][jCur].Cell = ' ';
		this->showGrid[iCur][jCur].emptyFull = EMPTY;

		return true;
	}
	void warriorKilled(int i, int j, char zombie) { //i,j here are the new coordinates of the warrior
		this->grid[i][j].Cell = zombie;
		this->grid[i][j].derick = 0;
		this->grid[i][j].chiconne = 0;
		this->showGrid[i][j].Cell = zombie;
		this->showGrid[i][j].derick = 0;
		this->showGrid[i][j].chiconne = 0;
	}
	Coord* returnLZ(void) {
		int i, j, mem = H_LZ, a = 0;
		Coord*LZ = new Coord[mem];
		for (i = 0; i < this->size; i++) {
			for (j = 0; j < this->size; j++) {
				if (this->grid[i][j].Cell == 'L') {
					LZ[a].x = i; LZ[a].y = j;
					a++;
				}
			}
		}
		return LZ;
	}
	Coord* returnMZ(void) {
		int i, j, mem = H_MZ, a = 0;
		Coord* MZ = new Coord[mem];
		for (i = 0; i < this->size; i++) {
			for (j = 0; j < this->size; j++) {
				if (this->grid[i][j].Cell == 'M') {
					MZ[a].x = i; MZ[a].y = j;
					a++;
				}
			}
		}
		return MZ;
	}
	Coord* returnSZ(void) {
		int i, j, mem = H_SZ, a = 0;
		Coord* SZ = new Coord[mem];
		for (i = 0; i < this->size; i++) {
			for (j = 0; j < this->size; j++) {
				if (this->grid[i][j].Cell == 'S') {
					SZ[a].x = i; SZ[a].y = j;
					a++;
				}
			}
		}
		return SZ;
	}
	Coord* returnLMK(void) {
		int i, j, mem = H_LMK, a = 0;
		Coord* LMK = new Coord[mem];
		for (i = 0; i < this->size; i++) {
			for (j = 0; j < this->size; j++) {
				if (this->grid[i][j].Cell == '*') {
					LMK[a].x = i; LMK[a].y = j;
					a++;
				}
			}
		}
		return LMK;
	}
	Coord* returnSMK(void) {
		int i, j, mem = H_SMK, a = 0;
		Coord* SMK = new Coord[mem];
		for (i = 0; i < this->size; i++) {
			for (j = 0; j < this->size; j++) {
				if (this->grid[i][j].Cell == '+') {
					SMK[a].x = i; SMK[a].y = j;
					a++;
				}
			}
		}
		return SMK;
	}
	Coord* returnAmmo(void) {
		int i, j, mem = H_Ammo, a = 0;
		Coord* Ammo = new Coord[mem];
		for (i = 0; i < this->size; i++) {
			for (j = 0; j < this->size; j++) {
				if (this->grid[i][j].Cell == 'A') {
					Ammo[a].x = i; Ammo[a].y = j;
					a++;
				}
			}
		}
		return Ammo;
	}
	gridCell** getGrid(void) {
		return this->grid;
	}
	int getAmmo(void) {
		return H_Ammo;
	}
	int getLMK(void) {
		return H_LMK;
	}
	int getSMK(void) {
		return H_SMK;
	}
	int getLZ(void) {
		return H_LZ;
	}
	int getMZ(void) {
		return H_MZ;
	}
	int getSZ(void) {
		return H_SZ;
	}
	Coord getDerick (void){
		int i, j;
		Coord derick;
		for (i = 0; i < this->size; i++) {
			for (j = 0; j < this->size; j++) {
				if (this->grid[i][j].Cell == 'D') {
					derick.x = i; derick.y = j;
					return derick;
				}
			}
		}
	}

	Coord getChiconne(void) {
		int i, j;
		Coord chiconne;
		for (i = 0; i < this->size; i++) {
			for (j = 0; j < this->size; j++) {
				if (this->grid[i][j].Cell == 'C') {
					chiconne.x = i; chiconne.y = j;
					return chiconne;
				}
			}
		}
	}
};

