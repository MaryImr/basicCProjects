#include <iostream>

using std::cout;
using std::endl;

#ifndef WARRIOR_H
#define WARRIOR_H

typedef struct Coordinates { //structure to store coordinates for anything in the grid
	int x;
	int y;
}Coord;

class Warrior {
private:
	int Warrior_Health;
	bool is_alive;
	Coord Warrior_Coord;
	int zombie_counter;
protected:
	int zombies_head[100]; //to store what zombies a warrior has killed 
	int Warrior_Dmg;
public:
	Warrior();
	void set_Warrior_Health();  //setter/getter/adder for warrior health
	int get_Warrior_Health();
	void add_warrior_health(int);
	
	void set_Warrior_Coord(Coord);  //setter/getter for current warrior coordinates
	Coord get_Warrior_Coord();

	void set_zombie_counter();  //setter/getter for number of zombies killed
	int get_zombie_counter();

	bool IS_alive();   //indicates if warrior alive or dead
	void add_zombie_head(int);      //adds another kill to the player's killed array
	void zombie_attack(int);        //if player dies of a zombie attack
	virtual char get_represent() = 0;     //other helper functions
	virtual void set_Warrior_Ammo()=0;
	virtual int get_Warrior_Ammo()=0;
	virtual void add_resource(char)=0;
	virtual int get_Warrior_Dmg(int)=0;
	virtual int print_score()=0;
	virtual void print_warrior_stat() = 0;
};

class Derick :public Warrior {
private:
	char represnt;
	int Warrior_Ammo;
public:
	Derick();
	char get_represent();
	void set_Warrior_Ammo();
	int get_Warrior_Ammo();
	void add_resource(char);
	int get_Warrior_Dmg(int);
	int print_score();
	void print_warrior_stat();
};

class Chichonne:public Warrior {
private:
	char represnt;
	int Warrior_Ammo;
public:
	Chichonne();
	char get_represent();
	void set_Warrior_Ammo();
	int get_Warrior_Ammo();
	void add_resource(char);
	int get_Warrior_Dmg(int);
	int print_score();
	 void print_warrior_stat();
};
#endif
//=======================================================================================================
Warrior::Warrior() {
	Warrior_Health = 100;
	Warrior_Dmg = 5;
	is_alive = true;
	Warrior_Coord.x = -1;
	Warrior_Coord.y = -1;
	zombie_counter = 0;
}
void Warrior::set_Warrior_Health() {
	Warrior_Health = 100;
}

int Warrior::get_Warrior_Health() {
	return Warrior_Health;
}
void Warrior::add_warrior_health(int health) {
	Warrior_Health += health;
}
void Warrior::set_Warrior_Coord(Coord position) {
	Warrior_Coord = position;
}
Coord Warrior::get_Warrior_Coord() {
	return Warrior_Coord;
}
void Warrior::set_zombie_counter() {
	zombie_counter = 0;
}
int Warrior::get_zombie_counter() {
	return zombie_counter;
}
void Warrior::add_zombie_head(int size) {
	zombies_head[zombie_counter] = size;
	zombie_counter++;
}
void Warrior::zombie_attack(int attack) {
	Warrior_Health -= attack;
	if (Warrior_Health <= 0) {
		is_alive = false;
		cout << "\nDIED" << endl;
	}
}
bool Warrior::IS_alive() {
	return is_alive;
}
//=========================================================================
Chichonne::Chichonne():Warrior() {
	represnt = 'C';
	Warrior_Ammo = 25;
}
void Chichonne::set_Warrior_Ammo() {
	Warrior_Ammo = 25;
}
char Chichonne::get_represent() {
	return represnt;
}
int Chichonne::get_Warrior_Ammo() {
	return Warrior_Ammo;
}
void Chichonne::add_resource(char type) {
	switch (type) {
		case '*':
			add_warrior_health(20);
			break;
		case '+':
			add_warrior_health(10);
			break;
		case 'A':
			Warrior_Ammo += 10;
			break;
		default:
			break;
	}
}
int Chichonne::get_Warrior_Dmg(int dice_roll) {
	if (Warrior_Ammo > 0) {
		Warrior_Ammo--;
		if ((dice_roll == 5) || (dice_roll == 6))
			return Warrior_Dmg*2;
		else if ((dice_roll == 1) || (dice_roll == 2))
			return Warrior_Dmg / 2;
		else
			return Warrior_Dmg;
	}
	else {
		if (get_zombie_counter() >= 2)
			return Warrior_Dmg+1;
		else
			return Warrior_Dmg-1;
	}
}

int Chichonne::print_score()
{
	int i,total_score=0;
	cout << "(Chichonne) killed: " << get_zombie_counter() << endl;;
	
	for (i = 0; i < get_zombie_counter(); i++) {
		switch (zombies_head[i]) {
			case 1:
				cout << " Small Zombie, ";
				total_score += 50;
				break;
			case 2:
				cout << " Medium Zombie, ";
				total_score += 75;
				break;
			case 3:
				cout << " Large Zombie, ";
				total_score += 100;
				break;
			default:
				break;
		}
	}
	cout << "\nTotal score : " << total_score << endl;
	return total_score;
}
//============================================================================================================
Derick::Derick() :Warrior() {
	represnt = 'D';
	Warrior_Ammo = 30;
}
char Derick::get_represent() {
	return represnt;
}
void Derick::set_Warrior_Ammo() {
	Warrior_Ammo = 30;
}
int Derick::get_Warrior_Ammo() {
	return Warrior_Ammo;
}
void Derick::add_resource(char type) {
	switch (type) {
		case '*':
			add_warrior_health(20);
			break;
		case '+':
			add_warrior_health(10);
			break;
		case 'A':
			Warrior_Ammo += 10;
			break;
		default:
			break;
	}
}
int Derick::get_Warrior_Dmg(int dice_roll) {
	if (Warrior_Ammo > 1) {
		Warrior_Ammo -= 2;
		if ((dice_roll == 5) || (dice_roll == 6))
			return Warrior_Dmg * 4;
		else if ((dice_roll == 1) || (dice_roll == 2))
			return 4;
		else
			return Warrior_Dmg*2;

	}
	else if (Warrior_Ammo == 1) {
		Warrior_Ammo--;
		return Warrior_Dmg;
	}
	else
		return 0;
}
int Derick::print_score()
{
	int i, total_score = 0;
	cout << "(Derick) has killed: "<< get_zombie_counter()<<endl;
	for (i = 0; i < get_zombie_counter(); i++) {
		switch (zombies_head[i]) {
			case 1:
				cout << " Small Zombie, ";
				total_score += 50;
				break;
			case 2:
				cout << " Medium Zombie, ";
				total_score += 75;
				break;
			case 3:
				cout << " Large Zombie, ";
				total_score += 100;
				break;
			default:

				break;
		}
	}
	cout << "\nTotal score : " << total_score << endl;
	return total_score;
}

void  Derick::print_warrior_stat() {
	cout << "Warrior name:Derick\nWarrior Health: "<<get_Warrior_Health()<<"\nwarrior ammounitation: "<<get_Warrior_Ammo();
	cout << "\nzombie slayed: " << get_zombie_counter() << "\ncoordinates : x -- " << get_Warrior_Coord().x << ", y -- " << get_Warrior_Coord().y<<endl;	
}

void  Chichonne::print_warrior_stat() {
	cout << "Warrior name:Chichonne\nWarrior Health: " <<get_Warrior_Health() << "\nWarrior Ammunation: " << get_Warrior_Ammo();
	cout << "\nZombies Slayed: " << get_zombie_counter() << "\nCoordinates : x -- " <<get_Warrior_Coord().x << ", y -- " << get_Warrior_Coord().y << endl;	
}