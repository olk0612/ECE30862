/*
 * Map.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: xiao81
 */

#ifndef MAP_HPP_
#define MAP_HPP_
#include "header.hpp"
#include "Room.hpp"
#include "Container.hpp"
#include "Item.hpp"
#include "Creature.hpp"

class Map {
public:
	map<string,Room*> room_map;
	map<string,Container*> container_map;
	map<string,Item*> item_map;
	map<string,Creature*> creature_map;

	Map(const char *filename){
		parse_file(filename);
	}
	virtual ~Map(){};
private:

	void parse_file(const char *filename) {
		file<> xml_file(filename);
		xml_document<> doc;
		doc.parse<0>(xml_file.data());
		xml_node<> *node = doc.first_node();
		for(xml_node<>*top = node -> first_node(); top; top = top -> next_sibling()){
			if (string(top->name()) == "item") {
				Item* item = new Item(top);
				item_map[item->name] = item;
			}
			if (string(top->name()) == "container") {
				Container* container = new Container(top);
				container_map[container->name] = container;

			}
			if (string(top->name()) == "room") {
				Room* room = new Room(top);
				room_map[room->name] = room;
			}
			if (string(top->name()) == "creature") {
				Creature* creature = new Creature(top);
				creature_map[creature->name] = creature;
			}
		}
	}
};

#endif /* Map_HPP_ */
