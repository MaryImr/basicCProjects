#include <iostream>

#include "fight.h"
using std::endl;

#ifndef entity_H
#define entity_H

class Entity {
private: //arrays to store each object's coordinate information 
	LargeZ* LZ;
	MediumZ* MZ;
	SmallZ* SZ;
	Lmidkit* Lmkit;
	Smidkit* Smkit;
	ammo* AMmo;
public:  //within the game, there is 1 derick and 1 chiconne. Players cannot be both derick or both chiconne at the same time!
	Derick D1;  
	Chichonne C1;
	Entity(int,int,int,int,int,int);  //constructor to allocate memory to each object array 
	void fill_largeZ(Coord*, int); //set coordinates of each large zombie in the array
	void fill_margeZ(Coord*, int); //set coordinates of each medium zombie in the array
	void fill_sargeZ(Coord*, int); //set coordinates of each small zombie in the array
	void fill_largeMIDKIT(Coord*, int); //set coordinates of each large medkit in the array
	void fill_smallMIDKIT(Coord*, int); //set coordinates of each small medkit in the array
	void fill_ammo(Coord*, int);   //set coordinates of each ammo bundle in the array
	char battle(char, Coord, char, int);   //slightly decieving name, this function accounts for all actions to be taken on any cell in the grid
	bool are_dead();   //to check if both warriors are dead
	void players_score();   //to print each player's score
	void print_whole_entity_info(int, int, int, int, int, int);  //to print information about the whole entity
	void display_winner();  //to decide and display the winner of the game
};

#endif
Entity::Entity(int LZsize, int MZsize, int SZsize, int LMKsize, int SMKsize, int AMMOsize) { //takes the amount of each hidden object available in the grid
	LZ = new LargeZ[LZsize];
	MZ = new MediumZ[MZsize];
	SZ = new SmallZ[SZsize];
	Lmkit = new Lmidkit[LMKsize];
	Smkit = new Smidkit[SMKsize];
	AMmo = new ammo[AMMOsize];
}

void Entity::fill_margeZ(Coord* arr, int size) {  //take an array with coordinates of each medium zombie, and the size of the grid
	for (int i = 0; i < size; i++)
		MZ[i].set_coord(arr[i]); //setting coordinates in the array of each medium zombie in the grid
}

void Entity::fill_largeZ(Coord* arr, int size) {   //take an array with coordinates of each large zombie, and the size of the grid
	for (int i = 0; i < size; i++)
		LZ[i].set_coord(arr[i]);  //setting coordinates in the array of each large zombie in the grid
}

void Entity::fill_sargeZ(Coord* arr, int size) {   //take an array with coordinates of each small zombie, and the size of the grid
	for (int i = 0; i < size; i++)
		SZ[i].set_coord(arr[i]);  //setting coordinates in the array of each small zombie in the grid
}
void Entity::fill_largeMIDKIT(Coord* arr, int size) {   //take an array with coordinates of each large medkit, and the size of the grid
	for (int i = 0; i < size; i++)
		Lmkit[i].set_coord(arr[i]);  //setting coordinates in the array of each large medkit in the grid
}
void Entity::fill_smallMIDKIT(Coord* arr, int size) {   //take an array with coordinates of each small medkit, and the size of the grid
	for (int i = 0; i < size; i++)
		Smkit[i].set_coord(arr[i]);  //setting coordinates in the array of each small medkit in the grid
}

void Entity::fill_ammo(Coord* arr, int size) {    //take an array with coordinates of each ammo bundle, and the size of the grid
	for (int i = 0; i < size; i++)
		AMmo[i].set_coord(arr[i]);  //setting coordinates in the array of each ammo bundle in the grid
}

char Entity::battle(char warrior_rep, Coord entity_corrd, char Entity_type,int size) {
	
	//the battlefunction called in each case below with the relevent element of the relevent array applies the correct actions
	//and returns D (for derick)/C (for chiconne) if the warrior wins 
	//and L (for large zombie)/M (for medium zombie)/S(for small zombie) if the zombie wins! 

	//for each case below, if it's derick's turn, D1 is sent as the warrior to the battle function
	//and it it's chiconne's turn, C1 is sent as the warrior to the battle function

	//similarly, according to the hidden object found on the cell, the relevant array is traversed to find the object 
	//with same coordinates as the one that the player found. 
	//That specific object is then sent to the battlefunction to interact with the player

	if (warrior_rep == 'D') {  //if derick's turn
		switch (Entity_type) {
			case 'L':  
				for (int i = 0; i < size; i++) { 
					if ((entity_corrd.x == (LZ[i].get_coord().x)) && (entity_corrd.y == (LZ[i].get_coord().y))) {
						return battelfunction(D1, LZ[i]); 
						break;
					}
				}
				break;
			case 'M':  
				for (int i = 0; i < size; i++) {
					if ((entity_corrd.x == (MZ[i].get_coord().x)) && (entity_corrd.y == (MZ[i].get_coord().y))) {
						return battelfunction(D1, MZ[i]);
						break;
					}
				}
				break;
			case 'S':  
				for (int i = 0; i < size; i++) { 
					if ((entity_corrd.x == (SZ[i].get_coord().x)) && (entity_corrd.y == (SZ[i].get_coord().y))) {
						return battelfunction(D1, SZ[i]);
						break;
					}
				}
				break;
			case '*':  
				for (int i = 0; i < size; i++) { 
					if ((entity_corrd.x == (Lmkit[i].get_coord().x)) && (entity_corrd.y == (Lmkit[i].get_coord().y))) {
						return battelfunction(D1, Lmkit[i]);
						break;
					}
				}
				break;
			case '+':  
				for (int i = 0; i < size; i++) { 
					if ((entity_corrd.x == (Smkit[i].get_coord().x)) && (entity_corrd.y == (Smkit[i].get_coord().y))) {
						return battelfunction(D1, Smkit[i]);
						break;
					}
				}
				break;
			case 'A':  
				for (int i = 0; i < size; i++) { 
					if ((entity_corrd.x == (AMmo[i].get_coord().x)) && (entity_corrd.y == (AMmo[i].get_coord().y))) {
						return battelfunction(D1, AMmo[i]);
						break;
					}
				}
				break;
			default:  //if nothing found on the coordinates the players wants to move to
				cout << "\nPlayer has moved to a safe spot, you live for another day!\n" << endl;
				return 'D';
				break;
		}
	}
	if (warrior_rep == 'C') {
		switch (Entity_type) {
			case 'L':
				for (int i = 0; i < size; i++) {
					if ((entity_corrd.x == (LZ[i].get_coord().x)) && (entity_corrd.y == (LZ[i].get_coord().y))) {
						return battelfunction(C1, LZ[i]);
						break;
					}
				}
				break;
			case 'M':
				for (int i = 0; i < size; i++) {
					if ((entity_corrd.x == (MZ[i].get_coord().x)) && (entity_corrd.y == (MZ[i].get_coord().y))) {
						return battelfunction(C1, MZ[i]);
						break;
					}
				}
				break;
			case 'S':
				for (int i = 0; i < size; i++) {
					if ((entity_corrd.x == (SZ[i].get_coord().x)) && (entity_corrd.y == (SZ[i].get_coord().y))) {
						return battelfunction(C1, SZ[i]);
						break;
					}
				}
				break;
			case '*':
				for (int i = 0; i < size; i++) {
					if ((entity_corrd.x == (Lmkit[i].get_coord().x)) && (entity_corrd.y == (Lmkit[i].get_coord().y))) {
						return battelfunction(C1, Lmkit[i]);
						break;
					}
				}
				break;
			case '+':
				for (int i = 0; i < size; i++) {
					if ((entity_corrd.x == (Smkit[i].get_coord().x)) && (entity_corrd.y == (Smkit[i].get_coord().y))) {
						return battelfunction(C1, Smkit[i]);
						break;
					}
				}
				break;
			case 'A':
				for (int i = 0; i < size; i++) {
					if ((entity_corrd.x == (AMmo[i].get_coord().x)) && (entity_corrd.y == (AMmo[i].get_coord().y))) {
						return battelfunction(C1, AMmo[i]);
						break;
					}
				}
				break;
			default:
				cout << "\nPlayer has moved to a safe spot, you live for another day!\n" << endl;
				return 'C';
				break;
		}
	}
}

bool Entity::are_dead() {
	if ((D1.IS_alive() == false) && (C1.IS_alive() == false))
		return true;
	return false;
}
void Entity::players_score() {
	D1.print_score();
	C1.print_score();
}
void Entity::print_whole_entity_info(int LZsize, int MZsize, int SZsize, int LMKsize, int SMKsize, int AMMOsize) {
	cout << "=================================================" << endl;
	D1.print_warrior_stat();
	cout << "=================================================" << endl;
	C1.print_warrior_stat();
	cout << "=================================================" << endl;

	//to print stats and coordinates of each hidden object on the grid, for code tester's convenience
	/*for (int i = 0; i < LZsize; i++)
		cout << "large zombie: " << LZ[i].get_zombie_life() << "life:" << LZ[i].get_zombie_life() << "dmg:" << LZ[i].get_zombiedmg() << "size:" << LZ[i].get_zombie_size() << "coord:x " << LZ[i].get_coord().x << " y " << LZ[i].get_coord().y << endl;
		
	cout << "=================================================" << endl;

	for (int i = 0; i < MZsize; i++)
		cout << "medium zombie: " << MZ[i].get_zombie_life() << "life:" << MZ[i].get_zombie_life() << "dmg:" << MZ[i].get_zombiedmg() << "size:" << MZ[i].get_zombie_size() << "coord:x " << MZ[i].get_coord().x << " y " << MZ[i].get_coord().y << endl;

	cout << "=================================================" << endl;

	for (int i = 0; i < SZsize; i++)
		cout << "small zombie: " << SZ[i].get_zombie_life() << "life:" << SZ[i].get_zombie_life() << "dmg:" << SZ[i].get_zombiedmg() << "size:" << SZ[i].get_zombie_size() << "coord:x " << SZ[i].get_coord().x << " y " << SZ[i].get_coord().y << endl;

	cout << "=================================================" << endl;

	for (int i = 0; i < LMKsize; i++)
		cout << "large midkit: "  << "coord:x " << Lmkit[i].get_coord().x << " y " << Lmkit[i].get_coord().y << endl;

	cout << "=================================================" << endl;

	for (int i = 0; i < SMKsize; i++)
		cout << "small midkit: " << "coord:x " << Smkit[i].get_coord().x << " y " << Smkit[i].get_coord().y << endl;
	
	cout << "=================================================" << endl;

	for (int i = 0; i < AMMOsize; i++)
		cout << "ammo midkit: " << "coord:x " << AMmo[i].get_coord().x << " y " << AMmo[i].get_coord().y << endl;*/	
}

void Entity::display_winner() {
	int s1, s2;
	s1 = D1.print_score();
	s2 = C1.print_score();
	if (s1 > s2)
		cout << "\nCongratulations Derick, you have beaten Chichonne!\n";

	else if (s2 > s1) 
		cout << "\nCongratulations Chichonne, you have beaten Derick!\n";

	else
		cout << "\nCongratulations, Both Warriors have the same score!\n";
}

