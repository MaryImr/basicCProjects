#include "resources.h"
#include <stdlib.h>     /* srand, rand */
#include <ctime> 

char battelfunction(Warrior &player,Zombie &monster) { //for fight with zombie
	cout << "\n==================\nDANGER !! DANGER!!\n==================\nPlayer has approched a zombie: ";
	monster.you_found();
	srand(time(NULL));
	int attack,dice;
	cout << "\nTHE BATTLE HAS STARTED!! DEFEAT THE ZOMBIE"<<endl;
	cout << "\nPlayer stats:" << endl;
	player.print_warrior_stat();
	do {
		cout << "\nPlayer's turn, DICE is rolled" << endl;
		dice = rand() % 6 + 1; //dice roll
		cout << "You got " << dice << endl;
		attack = player.get_Warrior_Dmg(dice); //damage calculation
		monster.dmg_dlt_to_zombie(attack); //dealing damage to zombie
		cout << "Player has dealt " << attack << " DMG to zombie\nZombie's current health :" << monster.get_zombie_life() << endl;
		if (monster.Is_alive() == false) { //if zombie was killed
			cout << "Player has slayed the zombie!" << endl;
			switch (monster.get_represnt()) {  //adding killed zombie to kills of the warrior
				case 'L':
					player.add_zombie_head(3);
					break;
				case 'M':
					player.add_zombie_head(2);
					break;
				case 'S':
					player.add_zombie_head(1);
					break;
				default:
					break;
			}
			player.print_score();
			return player.get_represent();  //returning player as the winner
		}
		//else if zombie doesn't die
		cout << "\nZombie's turn" << endl;
		player.zombie_attack(monster.get_zombiedmg()); //dealing damage to player
		cout << "\nZombie has dealt " << monster.get_zombiedmg() << " DMG to player\nPlayer's current health: " << player.get_Warrior_Health() << endl;
		if (player.IS_alive() == false) { //if player dies
			cout << "Zombie has devoured the player" << endl;
			return monster.get_represnt();  //returning zombie as the winner
		}
	} while (true);
	cout << "\n";
}

char battelfunction(Warrior& player,resource &item) {  //for toring resource
	switch (item.get_represnt()) {
		case '*':
			cout << "\nPlayer has found ";
			item.you_found();
			player.add_resource('*');
			cout << "\nPlayer's health has increased to " << player.get_Warrior_Health()<<endl;
			cout << "\n";
			break;
		case '+':
			cout << "\nPlayer has found ";
			item.you_found();
			player.add_resource('+');
			cout << "\nPlayer's health has increased to " << player.get_Warrior_Health()<<endl;
			cout << "\n";
			break;
		case 'A':
			cout << "\nPlayer has found ";
			item.you_found();
			player.add_resource('A');
			cout << "\nPlayer's ammo has increased to " << player.get_Warrior_Ammo() << endl;
			cout << "\n";
			break;
		default:
			break;
	}
	return player.get_represent(); //return player since to fight happened
}