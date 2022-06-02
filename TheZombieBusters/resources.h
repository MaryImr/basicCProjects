#include"zombie.h"
#ifndef resource_H
#define resource_H

class resource {
	Coord resource_coord; //coordinates of particular resource on the grid
protected:
	char represnt;  //symbol for the resource
public:
	resource();
	virtual char get_represnt()=0;
	virtual void you_found()=0;
	void set_coord(Coord);
	Coord get_coord();
};

class Lmidkit : public resource {
public:
	Lmidkit();
	char get_represnt();
	void you_found();
};

class Smidkit : public resource {
public:
	Smidkit();
	char get_represnt();
	void you_found();
};

class ammo : public resource {
public:
	ammo();
	char get_represnt();
	void you_found();
};
#endif 

resource::resource() {
	represnt = '0';
	resource_coord.x = -1;
	resource_coord.y = -1;
}
void resource::set_coord(Coord position) {
	resource_coord = position;
}
Coord resource::get_coord() {
	return resource_coord;
}
//==========================================
Lmidkit::Lmidkit() :resource() {
	represnt = '*';
}
char Lmidkit::get_represnt() {
	return represnt;
}

void Lmidkit::you_found() {
	cout << "Large Medicine Kit : Life points +20!";
}
//============================================
Smidkit::Smidkit() :resource() {
	represnt = '+';
}
char Smidkit::get_represnt() {
	return represnt;
}

void Smidkit::you_found() {
	cout << "Small Medicine Kit : Life points +10!";
}
//==============================================
ammo::ammo() :resource() {
	represnt = 'A';
}
char ammo::get_represnt() {
	return represnt;
}
void ammo::you_found() {
	cout << "Ammunition : Ammunition +10!";
}