/* Maryam Imran - 2413284 -- Mohammad Said Alqudaimi -  2414571
I read and accept the submission rules and the important section specified in assignment file.
This is my own work that is done by myself and my team - mate only */


#include <iostream>
#include "Grid.h"
#include "helper.h"


using std::cout;
using std::cin;
using std::endl;

int main() {
	int size;
	char dc;

	cout << "HELLO Players:\nWelcome to The Zombie Busters: Cleaning of Paradise Island from Zombie Infection!" << endl;
	size = getSize();

	Grid Board(size);  //creating the grid, randomly placing hidden objects and characters on the grid
	//cout <<"\n" <<Board.getLZ() << " " << Board.getMZ() << " " << Board.getSZ() << " " << Board.getLMK() << " " << Board.getSMK() << " " << Board.getAmmo() << " " << "\n" << endl;
	Entity objects(Board.getLZ(), Board.getMZ(), Board.getSZ(), Board.getLMK(), Board.getSMK(), Board.getAmmo()); //initializing entity

	//initializing arrays of objects with the respective objects' coordinates from the grid
	initializeObjects(Board, objects);

	//welcome statements
	printf("**********************************************************************");
	objects.print_whole_entity_info(Board.getLZ(), Board.getMZ(), Board.getSZ(), Board.getLMK(), Board.getSMK(), Board.getAmmo());
	//Board.printGrid2();            //in case you want to print the grid that shows any hidden objects
	cout << "The grid has been created\nThe Mission has started\nObjective: Clear the Island from Infected Zombies! " << endl;
	cout << "Some Information before you start:" << endl;
	cout << "     There are hidden objects on the grid!" << endl;
	cout << "     Your resources increase if you find ammunation or a medkit!" << endl;
	cout << "     You have to fight a zombie if you find it!" << endl;
	cout << "     If you die fighting a zombie, it will be visible to the other player!" << endl;
	cout << "     You cannot visit the same part of the grid again, but both players can visit the same part once each!" << endl;
	cout << "     If any player visits a part of the grid, it will be shown as blank space if when the player moves away from it (even if the other player has not yet visited it)!" << endl;
	cout << "     When asked for coordinates, x is the vertical value & y is the horizontal value!" << endl;
	cout << "\nENJOY!\n" << endl;

	//the game runs

	do {
		cout << "Who wants their turn first (D for Derick, C for Chiconne): "; cin >> dc;
		if (dc != 'C' && dc != 'D')
			cout << "\nInvalid Input!";
	} while (dc != 'C' && dc != 'D');

	cout << "\n\n";

	switch (dc) {
	case 'D':
		do {
			//Board.printGrid2(); cout << "\n";
			Board.printGrid();
			turnDerick(Board, objects, size);
			//Board.printGrid2(); cout << "\n";
			Board.printGrid();
			if ((Board.gameEnd() == true) || (objects.are_dead() == true))
				break;
			turnChiconne(Board, objects, size);
			if ((Board.gameEnd() == true) || (objects.are_dead() == true))
				break;
		} while (true);
		break;

	case 'C':
		do {
			//Board.printGrid2(); cout << "\n";
			Board.printGrid();
			turnChiconne(Board, objects, size);
			//Board.printGrid2(); cout << "\n";
			Board.printGrid();
			if ((Board.gameEnd() == true) || (objects.are_dead() == true))
				break;
			turnDerick(Board, objects, size);
			if ((Board.gameEnd() == true) || (objects.are_dead() == true))
				break;
		} while (true);
		break;
	}

	//Board.printGrid();
	gameResults(Board, objects);
}
