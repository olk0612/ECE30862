/*
 * main.cpp
 *
 *  Created on: Dec 9, 2016
 *      Author: xiao81
 */
#include "header.hpp"
#include "Item.hpp"
#include "Container.hpp"
#include "Room.hpp"
#include "Creature.hpp"
#include "Map.hpp"
#include "GameManager.hpp"
int main(int argc, char * argv[]) {

	Map* game_map = new Map(argv[1]);
	GameManager* gm = new GameManager(game_map);
	string input;
	string empty_input ="";
	bool override = false;
	cout << gm->curr_room->description << endl;
	while(true) {
		override = gm->check_trigger(empty_input);
		if(gm->game_over){
			break;
		}
		if(override) {
			continue;
		}
		getline(cin, input);
		if(input == "") {
			break;
		}

		override = gm->check_trigger(input);
		if(gm->game_over){
			break;
		}
		if(override) {
			continue;
		}

		gm->check_input(input);

		if(gm->game_over){
			break;
		}

	}
	return 0;
}
