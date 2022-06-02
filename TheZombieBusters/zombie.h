#include "warrior.h"
#ifndef Zombie_H
#define Zombie_H


class Zombie {
protected:
	char represnt;
	int zombie_dmg;
	int zombie_life;
	int zombie_size;
	Coord zombie_Coord;
	bool is_alive;
public:
	Zombie();
	virtual char get_represnt()=0;
	virtual int get_zombiedmg()=0;

	virtual int get_zombie_life() = 0;
	virtual void set_zombie_life() = 0;
	virtual void you_found() = 0;
	void dmg_dlt_to_zombie(int);
	bool Is_alive();
	
	Coord get_coord();
	void set_coord(Coord);

	int get_zombie_size();

};

class LargeZ:public Zombie {
public:
	LargeZ();
	char get_represnt();
	int get_zombiedmg();
	int get_zombie_life();
	void set_zombie_life();
	int get_Z_size();
	void you_found();
};
class MediumZ :public Zombie {
public:
	MediumZ();
	char get_represnt();
	int get_zombiedmg();
	int get_zombie_life();
	void set_zombie_life();
	int get_Z_size();
	void you_found();
};
class SmallZ :public Zombie {
public:
	SmallZ();
	char get_represnt();
	int get_zombiedmg();
	int get_zombie_life();
	void set_zombie_life();
	int get_Z_size();
	void you_found();
};
#endif
Zombie::Zombie() {
	represnt = '0';
	zombie_dmg = 0;
	zombie_life = 0;
	zombie_size = 0;
	zombie_Coord.x = -1;
	zombie_Coord.y = -1;
	is_alive = true;
}
void Zombie::dmg_dlt_to_zombie(int attacked)
{
	zombie_life-=attacked;
	if (zombie_life <= 0)
		is_alive = false;

}

bool Zombie::Is_alive() {
	return is_alive;
}

Coord Zombie::get_coord() {
	return zombie_Coord;
}

void Zombie::set_coord(Coord position) {
	zombie_Coord = position;
}

int Zombie::get_zombie_size()
{
	return zombie_size;
}
//=====================================================================================
LargeZ::LargeZ() :Zombie()
{
	represnt = 'L';
	zombie_dmg = 8;
	zombie_life = 12;
	zombie_size = 3;

}
void LargeZ::you_found() {
	cout << "Large zombie appeared:\nHealth: 12\nAttack DMG:8\nSize: 3"<<endl;

}
char LargeZ::get_represnt()
{
	return represnt;
}
int LargeZ::get_zombiedmg()
{
	return zombie_dmg;
}

int LargeZ::get_zombie_life()
{
	return zombie_life;
}

void LargeZ::set_zombie_life()
{
	zombie_life = 12;
}

int LargeZ::get_Z_size()
{
	return zombie_size;
}
//================================================================
MediumZ::MediumZ() :Zombie()
{
	represnt = 'M';
	zombie_dmg = 4;
	zombie_life = 8;
	zombie_size = 2;

}
void MediumZ::you_found() {
	cout << "Medium zombie appeared:\nHealth: 8\nAttack DMG:4\nSize: 2" << endl;

}
char MediumZ::get_represnt()
{
	return represnt;
}
int MediumZ::get_zombiedmg()
{
	return zombie_dmg;
}

int MediumZ::get_zombie_life()
{
	return zombie_life;
}

void MediumZ::set_zombie_life()
{
	zombie_life = 8;
}

int MediumZ::get_Z_size()
{
	return zombie_size;
}
//=============================================================
SmallZ::SmallZ() :Zombie()
{
	represnt = 'S';
	zombie_dmg = 2;
	zombie_life = 4;
	zombie_size = 1;
}
void SmallZ::you_found() {
	cout << "Small zombie appeared:\nHealth: 4\nAttack DMG:2\nSize: 1" << endl;

}
char SmallZ::get_represnt()
{
	return represnt;
}
int SmallZ::get_zombiedmg()
{
	return zombie_dmg;
}

int SmallZ::get_zombie_life()
{
	return zombie_life;
}

void SmallZ::set_zombie_life()
{
	zombie_life = 8;
}

int SmallZ::get_Z_size()
{
	return zombie_size;
}