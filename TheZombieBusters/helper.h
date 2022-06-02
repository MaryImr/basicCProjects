#include <iostream>

using std::cout;
using std::cin;
using std::endl;

bool checkAdjacent(Coord, int, int);
bool checkCoordinateExists(Coord, int);
int getSizeRequiredObjectArray(Grid, char);
void turnDerick(Grid&, Entity&, int);
void turnChiconne(Grid&, Entity&, int);
int getSize(void);
void initializeObjects(Grid&, Entity&);
void gameResults(Grid&, Entity&);

void gameResults(Grid& Board, Entity& objects) {
	if (Board.gameEnd() == true) {
		cout << "\n=========================================\n";
		cout << "Players have completed the mission!\nAll zombies have been slayed!" << endl;
		objects.display_winner();
	}
	else {
		cout << "GAME OVER!!\nBoth players are dead HAHAHAHAH!!!\n\n";
		objects.players_score();
	}
}

void initializeObjects(Grid &Board, Entity &objects) {
	//initializing arrays of objects with the respective objects' coordinates from the grid
	objects.fill_largeZ(Board.returnLZ(), Board.getLZ());
	objects.fill_margeZ(Board.returnMZ(), Board.getMZ());
	objects.fill_sargeZ(Board.returnSZ(), Board.getSZ());
	objects.fill_largeMIDKIT(Board.returnLMK(), Board.getLMK());
	objects.fill_smallMIDKIT(Board.returnSMK(), Board.getSMK());
	objects.fill_ammo(Board.returnAmmo(), Board.getAmmo());
	objects.D1.set_Warrior_Coord(Board.getDerick());
	objects.C1.set_Warrior_Coord(Board.getChiconne());
}

int getSize(void) {
	int size;
	do {
		cout << "Enter the size of the land (Warning: if you enter a size above 10, the grid might look a lottle wonky :) ): ";
		cin >> size; //taking size from user to define grid
		if (size < 5)
			cout << "\nSize should atleast be 5!\n" << endl;
	} while (size < 5);

	return size;
}

bool checkAdjacent(Coord coord, int x, int y) {
	if (((coord.x == x - 1) && (coord.y == y - 1)) || ((coord.x == x - 1) && (coord.y == y)) || ((coord.x == x - 1) && (coord.y == y + 1)) || ((coord.x == x) && (coord.y == y - 1)) || ((coord.x == x) && (coord.y == y + 1)) || ((coord.x == x + 1) && (coord.y == y - 1)) || ((coord.x == x + 1) && (coord.y == y)) || ((coord.x == x + 1) && (coord.y == y + 1)))
		return true;
	else
		return false;
}

bool checkCoordinateExists(Coord coord, int size) {
	if (((coord.x >= 0) && (coord.x < size)) && ((coord.y >= 0) && (coord.y < size)))
		return true;
	else
		return false;
}

int getSizeRequiredObjectArray(Grid Board, char pre) {
	int size;

	switch (pre) {
	case 'L':
		size = Board.getLZ();
		break;
	case 'M':
		size = Board.getMZ();
		break;
	case 'S':
		size = Board.getSZ();
		break;
	case '*':
		size = Board.getLMK();
		break;
	case '+':
		size = Board.getSMK();
		break;
	case 'A':
		size = Board.getAmmo();
		break;
	default:
		size = 0;
		break;
	}
	return size;
}


void turnDerick(Grid& Board, Entity& objects, int size) {

	int  size2, x, y;
	Coord coord, temp;
	char result, pre;
	bool checker, checker2;

	do {
		cout << "\nDerick's move:\nEnter X coordinates: ";
		cin >> coord.x;
		cout << "Enter Y coordinates: ";
		cin >> coord.y;
		
		temp = objects.D1.get_Warrior_Coord();
		x = temp.x; y = temp.y;
		checker = checkAdjacent(coord, x, y);
		checker2 = checkCoordinateExists(coord, size);

		if (checker == true && checker2 == true)
		{
			pre = Board.getCoordinateRep(coord.x, coord.y);
			if (Board.moveDerick(coord.x, coord.y) == true) {
				size2 = getSizeRequiredObjectArray(Board, pre);
				result = objects.battle('D', coord, pre, size2);
				if (result != 'D')
					Board.warriorKilled(coord.x, coord.y, result);
				break;
			}
			else
				cout << "\nInvaild coordinates, please try agian!\n";
		}
		else
			cout << "\nInvaild coordinates, please try agian!\n";
	} while (true);
	objects.D1.set_Warrior_Coord(Board.getDerick());
}

void turnChiconne(Grid& Board, Entity& objects, int size) {
	int size2, x, y;
	Coord coord, temp;
	char result, pre;
	bool checker, checker2;

	do {
		cout << "\nChichonne's move:\nEnter X coordinates: ";
		cin >> coord.x;
		cout << "Enter Y coordinates: ";
		cin >> coord.y;

		
		temp = objects.C1.get_Warrior_Coord();
		x = temp.x; y = temp.y;

		checker = checkAdjacent(coord, x, y);
		checker2 = checkCoordinateExists(coord, size);

		if (checker == true && checker2 == true)
		{
			pre = Board.getCoordinateRep(coord.x, coord.y);
			if (Board.moveChiconne(coord.x, coord.y) == true) {
				size2 = getSizeRequiredObjectArray(Board, pre);
				result = objects.battle('C', coord, pre, size2);
				if (result != 'C')
					Board.warriorKilled(coord.x, coord.y, result);
				break;
			}
			else
				cout << "\nInvaild coordinates, please try agian!\n";
		}
		else
			cout << "Invaild coordinates, please try agian!\n";
	} while (true);
	objects.C1.set_Warrior_Coord(Board.getChiconne());
}