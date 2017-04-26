/*
 * GameManager.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: xiao81
 */

#ifndef GAMEMANAGER_HPP_
#define GAMEMANAGER_HPP_
#include "header.hpp"
#include "Map.hpp"


class GameManager {
public:
	Map* game_map;
	Room* curr_room;
	bool game_over;
	vector<string> inventory;
	GameManager(Map* input_map){
		game_map = input_map;
		curr_room = game_map->room_map["Entrance"];
		game_over = false;
	}
	// Game Commands
	void check_input(string input) {
		if (input == "n" || input == "s" || input == "e" || input == "w") {
			move(input);
			return;
		}
		else if (input == "i") {
			get_inventory();
			return;
		}
		else if (input.find("take") != string::npos) {
			take(input.erase(0,5));
			return;
		}
		else if (input.find("open") != string::npos) {
			open(input.erase(0,5));
			return;
		}
		else if (input.find("read") != string::npos) {
			read(input.erase(0,5));
			return;
		}
		else if (input.find("drop") != string::npos) {
			drop(input.erase(0,5));
			return;
		}
		else if (input.find("put") != string::npos) {
			input.erase(0,4);
			int i = input.find(" ");
			string source = input.substr(0, i);
			input.erase(0, i+4);
			string target = input;
			put(source, target);
			return;
		}
		else if (input.find("turn on") != string::npos) {
			turnon(input.erase(0,8));
			return;
		}
		else if (input.find("attack") != string::npos) {
			input.erase(0,7);
			int i = input.find(" ");
			string creature_name = input.substr(0, i);
			input.erase(0, i+6);
			string weapon = input;
			attack(creature_name, weapon);
			return;
		}
		cout << "Error" << endl;

	}

	void move(string direction) {

		for (int i = 0; i < int(curr_room->border_list.size()); i++) {
			if (direction == curr_room->border_list[i]->direction) {
				curr_room = game_map->room_map[curr_room->border_list[i]->name];
				cout << curr_room->description << endl;
				return;
			}
		}
		cout << "Can't go that way" << endl;
		return;
	}

	void get_inventory() {

		if (inventory.size() == 0) {
			cout << "Inventory: empty" << endl;
			return;
		}

		cout << "Inventory: ";

		for (int i = 0; i < int(inventory.size()-1); i++) {
			cout << inventory[i] << ", ";
		}

		cout << inventory[inventory.size()-1] << endl;
	}

	void take(string input) {
		for (int i = 0; i < int(curr_room->item_list.size()); i++) {
			if (curr_room->item_list[i] == input) {
				inventory.push_back(input);
				curr_room->item_list.erase(curr_room->item_list.begin()+i);
				cout << "Item " << input << " added to inventory" << endl;
				return;
			}
		}

		for (int i = 0; i < int(curr_room->container_list.size()); i++) {
			Container* container = game_map->container_map[curr_room->container_list[i]];
			if (container->status == "unlocked") {
				for(int j = 0; j < int(container->item_list.size()); j++) {
					if (container->item_list[j] == input) {
						inventory.push_back(input);
						container->item_list.erase(container->item_list.begin()+j);
						cout << "Item " << input << " added to inventory" << endl;
						return;
					}
				}
			}
		}

		cout << input << " not found" << endl;

	}

	void open(string input) {
		if (input == "exit") {
			if (string(curr_room->type) == "exit") {
				cout << "Game Over" << endl;
				return;
			} else {
				cout << "You are not allowed to exit" << endl;
				return;
			}
		}
		if (curr_room->container_list.size() == 0) {
			cout << input << " not found" << endl;
			return;
		}
		for (int i = 0; i < int(curr_room->container_list.size()); i++) {

			if (curr_room->container_list[i] == input) {
				Container* container = game_map->container_map[curr_room->container_list[i]];
				if (container->status == "locked") {
					cout << input << " is locked" << endl;
					return;
				} else {
					container->status = "unlocked";
					if (container->item_list.size() == 0) {
						cout << input << " is empty" << endl;
						return;
					} else {
						cout << input << " contains ";
						for(int j = 0; j < int(container->item_list.size()-1); j++) {
							cout << container->item_list[j] << ", ";
						}
						cout << container->item_list[int(container->item_list.size()-1)] << endl;
						return;
					}
				}
			}
		}

		cout << input << " not found" << endl;

	}

	void read(string input) {
		for (int i = 0; i < int(inventory.size()); i++) {
			if (inventory[i] == input) {
				Item* item = game_map->item_map[input];
				if (item->writing.size() == 0) {
					cout << "Nothing written" << endl;
				} else {
					cout << item->writing << endl;
				}
				return;
			}
		}
		cout << input << " not in inventory" << endl;
	}

	void drop(string input) {
		for (int i = 0; i < int(inventory.size()); i++) {
			if (inventory[i] == input) {
				curr_room->item_list.push_back(input);
				inventory.erase(inventory.begin() + i);
				cout << input << " dropped" << endl;
				return;
			}
		}
		cout << input << " not in inventory" << endl;
	}

	void put(string source, string target) {
		if (std::find(inventory.begin(), inventory.end(), source) == inventory.end()) {
			cout << source << " not in inventory" << endl;
			return;
		}
		if (std::find(curr_room->container_list.begin(), curr_room->container_list.end(), target) == curr_room->container_list.end()) {
			cout << target << " not in the room" << endl;
			return;
		}

		for (int i = 0; i < int(inventory.size()); i++) {
			if (inventory[i] == source) {
				for (int j = 0; j < int(curr_room->container_list.size()); j++) {
					if (curr_room->container_list[j] == target) {

						Container* container = game_map->container_map[target];
						if (container->accept_list.size()>0) {
							if (std::find(container->accept_list.begin(), container->accept_list.end(), source) == container->accept_list.end()) {
								cout << source << " can not be placed in "<< target << endl;
								return;
							}
						}
						for (int k=0; k<int(container->accept_list.size());k++) {
							if (source == container->accept_list[k]) {
								inventory.erase(inventory.begin() + i);
								container->item_list.push_back(source);
								cout << "Item " << source << " added to " << target << endl;
								return;
							}
						}
						if (container->status == "locked") {
							cout << target << " is locked" << endl;
							return;
						} else {
							inventory.erase(inventory.begin() + i);
							container->item_list.push_back(source);
							cout << "Item " << source << " added to " << target << endl;
							return;
						}

					}
				}
			}
		}
	}

	void turnon(string input) {
		for (int i = 0; i < int(inventory.size()); i++) {
			if (inventory[i] == input) {
				Item* item = game_map->item_map[input];

				if (item->turn_on != NULL) {
					cout << "You activated " << item->name << endl;
					cout << item->turn_on->print << endl;
					check_action(item->turn_on->action);
					return;
				} else {
					cout << item << " can not be turned on" <<endl;
				}
			}
		}
		cout << input << " not in inventory" << endl;
	}

	void attack(string creature_name, string weapon) {
		if(std::find(curr_room->creature_list.begin(), curr_room->creature_list.end(), creature_name) == curr_room->creature_list.end()) {
			cout << creature_name << " is not in this room" << endl;
			return;
		}
		if (std::find(inventory.begin(), inventory.end(), weapon) == inventory.end()) {
			cout << weapon << " not in inventory" << endl;
			return;
		}
		cout << "You assault the " << creature_name << " with the " << weapon<< endl;
		Creature* creature = game_map->creature_map[creature_name];
		for(int i = 0; i < int(creature->vulnerability_list.size());i++) {
			if (creature->vulnerability_list[i] == weapon) {
				if (creature->attack == NULL) {
					return;
				}
				if (creature->attack->condition) {
					string object = creature->attack->condition->object;
					string status = creature->attack->condition->status;
					string object_type = type(object);
					bool condition = false;
					if(object_type == "Item"){
						if(game_map->item_map[object]) {
							if(game_map->item_map[object]->status == status){
								condition = true;
							}
						}
					}
					if(object_type == "Room"){
						if(game_map->room_map[object]) {
							if(game_map->room_map[object]->status == status){
								condition = true;
							}
						}
					}
					if(object_type == "Container"){
						if(game_map->container_map[object]) {
							if(game_map->container_map[object]->status == status){
								condition = true;
							}
						}
					}
					if(object_type == "Creature"){
						if(game_map->creature_map[object]) {
							if(game_map->creature_map[object]->status == status){
								condition = true;
							}
						}
					}
					if (!condition) {
						cout << object << " has to be in " << status << " status" << endl;
						return;
					}
				}
				if(creature->attack->print.size()>0) {
					cout << creature->attack->print << endl;
				}
				if (creature->attack->action_list.size()>0) {
					for(int i =0; i < int(creature->attack->action_list.size()); i++) {
						check_action(creature->attack->action_list[i]);
					}
				}
				return;
			}
		}
		cout << weapon << " has no effect on " << creature_name <<endl;

	}

	// Behind the Scenes Commands

	string type(string input) {
		if(game_map->container_map[input]) {
			return "Container";
		}
		else if (game_map->creature_map[input]) {
			return "Creature";
		}
		else if (game_map->room_map[input]) {
			return "Room";
		}
		else if (game_map->item_map[input]) {
			return "Item";
		}
		return "";
	}

	void add(string input){
		string object, destination;
		int i = input.find(" to ");
		object = input.substr(0, i);
		destination = input.substr(i + 4);
		string object_type = type(object);

		if(object_type == "Item"){
			if(game_map->room_map[destination]){
				game_map->room_map[destination]->item_list.push_back(object);
				return;
			}
			else if(game_map->container_map[destination]){
				game_map->container_map[destination]->item_list.push_back(object);
				return;
			}
	    }
		else if(object_type == "Creature"){
			game_map->room_map[destination]->creature_list.push_back(object);
			return;

		}
		else if(object_type == "Container"){
			if(game_map->room_map[destination]){
				game_map->room_map[destination]->container_list.push_back(object);
				return;
			}
		}
		cout << object<< " can not be added to " << destination << endl;
	}

	void del(string object){


		string object_type = type(object);
		if(object_type == "Item"){
			std::map<string, Room*>::iterator it;
			for(it = game_map->room_map.begin(); it != game_map->room_map.end(); ++it) {
				for(int i = 0; i < int(it->second->item_list.size()); i++) {
					if (it->second->item_list[i] == object) {
						game_map->room_map[it->first]->item_list.erase(game_map->room_map[it->first]->item_list.begin()+i);
					}
					return;
				}
			}
		}
		if(object_type == "Container"){
			std::map<string, Room*>::iterator it;
			for(it = game_map->room_map.begin(); it != game_map->room_map.end(); ++it) {
				for(int i = 0; i < int(it->second->container_list.size()); i++) {
					if (it->second->container_list[i] == object) {
						game_map->room_map[it->first]->container_list.erase(game_map->room_map[it->first]->container_list.begin()+i);
					}
					return;
				}
			}
		}
		if(object_type == "Creature"){

			std::map<string, Room*>::iterator it;
			for(it = game_map->room_map.begin(); it != game_map->room_map.end(); ++it) {
				for(int i = 0; i < int(it->second->creature_list.size()); i++) {
					if (it->second->creature_list[i] == object) {
						game_map->room_map[it->first]->creature_list.erase(game_map->room_map[it->first]->creature_list.begin()+i);
					}
					return;
				}
			}
		}
		if(object_type == "Room"){
			std::map<string, Room*>::iterator it;
			for(it = game_map->room_map.begin(); it != game_map->room_map.end(); ++it) {
					for(int i = 0; i < int(it->second->border_list.size()); i++) {
						if (it->second->border_list[i]->name == object) {
							it->second->border_list.erase(it->second->border_list.begin()+i);
							return;
						}

					}

			}
		}
		cout << object << " can not be deleted "<<endl;
	}

	void update(string input) {
		string object, status;
		int i = input.find(" to ");
		object = input.substr(0, i);
		status = input.substr(i + 4);
		string object_type = type(object);
		if(object_type == "Item"){
			if(game_map->item_map[object]){
				game_map->item_map[object]->status = status;
				return;
			}
		}
		else if(object_type == "Creature"){
			game_map->creature_map[object]->status= status;
			return;

		}
		else if(object_type == "Container"){

			game_map->container_map[object]->status= status;
			return;
		}
		cout << object << " can not be updated" << endl;
	}

	void GameOver(){
	    game_over = true;
	    cout << "Victory!" << endl;
	}
	void check_action(string action){
	    if(action.find("Add") != string::npos){
	        add(action.erase(0,4));
	        return;
	    }
	    if(action.find("Delete") != string::npos){
	        del(action.erase(0,7));
	        return;
	    }
	    if(action.find("Update") != string::npos){
	        update(action.erase(0,7));

	        return;
	    }
	    if(action == "Game Over"){
	        GameOver();
	        return;
	    }
	    check_input(action);
	}
	//Trigger

	void execute_trigger(Trigger* t) {
		if(t->print_list.size()>0) {
			for(int i =0; i <int(t->print_list.size());i++) {
				cout << t->print_list[i] << endl;
			}
		}
		if(t->action_list.size()>0) {
			for(int i =0; i <int(t->action_list.size());i++) {
				check_action(t->action_list[i]);
			}
		}
	}
	bool owner_trigger(Trigger* t) {
		string owner = t->owner->owner;
		string object = t->owner->object;
		string has = t->owner->has;

		if (owner == "inventory") {
			if (std::find(inventory.begin(), inventory.end(), object) == inventory.end()) {
				if(has == "no"){
					execute_trigger(t);
					return true;
				} else {
					return false;
				}
			}
			else {
				if(has == "yes"){
					execute_trigger(t);
					return true;
				} else {
					return false;
				}
			}
		}
		string owner_type = type(owner);
		string object_type = type(object);
		if (owner_type == "Room") {
			std::map<string, Room*>::iterator it_room;
			for(it_room = game_map->room_map.begin(); it_room != game_map->room_map.end(); ++it_room) {
				if (it_room->first == owner) {
					if(object_type == "Item") {
						for(int i = 0; i <int(it_room->second->item_list.size());i++) {
							if (it_room->second->item_list[i] == object) {
								if(has == "yes"){
									execute_trigger(t);
									return true;
								} else {
									return false;
								}
							}
						}
						if(has == "no"){
							execute_trigger(t);
							return true;
						} else {
							return false;
						}
					}else if(object_type == "Container") {
						for(int i = 0; i <int(it_room->second->container_list.size());i++) {
							if (it_room->second->container_list[i] == object) {
								if(has == "yes"){
									execute_trigger(t);
									return true;
								} else {
									return false;
								}
							}
						}
						if(has == "no"){
							execute_trigger(t);
							return true;
						} else {
							return false;
						}
					}else if(object_type == "Creature") {
						for(int i = 0; i <int(it_room->second->creature_list.size());i++) {
							if (it_room->second->creature_list[i] == object) {
								if(has == "yes"){
									execute_trigger(t);
									return true;
								} else {
									return false;
								}
							}
						}
						if(has == "no"){
							execute_trigger(t);
							return true;
						} else {
							return false;
						}
					}
				}
			}
		}else if (owner_type== "Container") {
			std::map<string, Container*>::iterator it_container;
			for(it_container = game_map->container_map.begin(); it_container != game_map->container_map.end(); ++it_container) {
				if (it_container->first == owner) {
					if(object_type == "Item") {
						for(int i = 0; i <int(it_container->second->item_list.size());i++) {
							if (it_container->second->item_list[i] == object) {
								if(has == "yes"){
									execute_trigger(t);
									return true;
								} else {
									return false;
								}
							}
						}
						if(has == "no"){
							execute_trigger(t);
							return true;
						} else {
							return false;
						}
					}
				}
			}
		}
		return false;
	}

	bool status_trigger(Trigger* t) {
		string object = t->status->object;
		string status = t->status->status;
		string object_type = type(object);

		if (object_type == "Room") {
			std::map<string, Room*>::iterator it_room;
			for(it_room = game_map->room_map.begin(); it_room != game_map->room_map.end(); ++it_room) {
				if (it_room->first == object) {
					if (it_room->second->status == status) {
						execute_trigger(t);
						return true;
					}
				}
			}
		}else if (object_type == "Item") {
			std::map<string, Item*>::iterator it_item;
			for(it_item = game_map->item_map.begin(); it_item != game_map->item_map.end(); ++it_item) {
				if (it_item->first == object) {
					if (it_item->second->status == status) {
						execute_trigger(t);
						return true;
					}
				}
			}
		}else if (object_type == "Container") {
			std::map<string, Container*>::iterator it_container;
			for(it_container = game_map->container_map.begin(); it_container != game_map->container_map.end(); ++it_container) {
				if (it_container->first == object) {
					if (it_container->second->status == status) {
						execute_trigger(t);
						return true;
					}
				}
			}
		}else if (object_type == "Creature") {
			std::map<string, Creature*>::iterator it_creature;
			for(it_creature = game_map->creature_map.begin(); it_creature != game_map->creature_map.end(); ++it_creature) {
				if (it_creature->first == object) {
					if (it_creature->second->status == status) {
						execute_trigger(t);
						return true;
					}
				}
			}
		}
		return false;

	}

	bool check_trigger(string input) {
		Trigger* t;
		bool room_result =false;
		bool item_result=false;
		bool container_result=false;
		bool creature_result=false;
		if(curr_room->trigger_list.size() > 0) {
			for(int i = 0; i <int(curr_room->trigger_list.size());i++) {
				t = curr_room->trigger_list[i];
				if ((t->command.size()>0 && input == t->command) || (t->command.size()==0 && input.size()==0)) {
					if(t->type == "permanent" || (t->type == "single" && t->count == 0)) {

						if(t->condition_count == 3) {
							room_result = owner_trigger(t);
						}else if(t->condition_count == 2) {
							room_result = status_trigger(t);
						}
						if(room_result) {
							t->count++;
						}
					}
				}
			}
		}
		for(int i = 0; i <int(curr_room->item_list.size());i++) {
			Item* item = game_map->item_map[curr_room->item_list[i]];
			for(int j = 0; j <int(item->trigger_list.size());j++) {
				t = item->trigger_list[j];
				if ((t->command.size()>0 && input == t->command) || (t->command.size()==0 && input.size()==0)) {
					if(t->type == "permanent" || (t->type == "single" && t->count == 0)) {
						if(t->condition_count == 3) {
							item_result = owner_trigger(t);
						}else if(t->condition_count == 2) {
							item_result = status_trigger(t);
						}
						if(item_result) {
							t->count++;
						}
					}
				}
			}
		}
		for(int i = 0; i <int(curr_room->container_list.size());i++) {
			Container* container = game_map->container_map[curr_room->container_list[i]];
			for(int j = 0; j <int(container->trigger_list.size());j++) {
				t = container->trigger_list[j];

				if ((t->command.size()>0 && input == t->command) || (t->command.size()==0 && input.size()==0)) {
					if(t->type == "permanent" || (t->type == "single" && t->count == 0)) {
						if(t->condition_count == 3) {
							container_result = owner_trigger(t);
						}else if(t->condition_count == 2) {
							container_result = status_trigger(t);
						}
						if(container_result) {
							t->count++;
						}
					}
				}
			}
		}
		for(int i = 0; i <int(curr_room->creature_list.size());i++) {
			Creature* creature = game_map->creature_map[curr_room->creature_list[i]];
			for(int j = 0; j <int(creature->trigger_list.size());j++) {
				t = creature->trigger_list[j];
				if ((t->command.size()>0 && input == t->command) || (t->command.size()==0 && input.size()==0)) {
					if(t->type == "permanent" || (t->type == "single" && t->count == 0)) {
						if(t->condition_count == 3) {
							creature_result = owner_trigger(t);
						}else if(t->condition_count == 2) {
							creature_result = status_trigger(t);
						}
						if(creature_result) {
							t->count++;
						}
					}
				}
			}
		}
		return room_result||item_result||container_result||creature_result;

	}

	virtual ~GameManager(){};
};

#endif /* GAMEMANAGER_HPP_ */
