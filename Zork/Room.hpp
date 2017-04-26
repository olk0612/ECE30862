/*
 * Room.hpp
 *
 *  Created on: Dec 9, 2016
 *      Author: xiao81
 */

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include "header.hpp"
#include "Border.hpp"
#include "Trigger.hpp"

class Room {
public:
	string name;
	string status;
	string type;
	string description;
	vector<Border*> border_list;
	vector<string> container_list;
	vector<string> item_list;
	vector<string> creature_list;
	vector<Trigger*> trigger_list;

	Room(xml_node<> *node){
		parse_room(node);
	}
	virtual ~Room(){};
private:
	void parse_room(xml_node<> *node) {
			for(xml_node<> *curr = node -> first_node(); curr; curr = curr -> next_sibling()) {
				if (string(curr->name()) == "name") {
					name = curr->value();
				}
				else if (string(curr->name()) == "type") {
					type = curr->value();
				}
				else if (string(curr->name()) == "status") {
					status = curr->value();
				}
				else if (string(curr->name()) == "description") {
					description = curr->value();
				}
				else if (string(curr->name()) == "item") {
					item_list.push_back(curr->value());
				}
				else if (string(curr->name()) == "container") {
					container_list.push_back(curr->value());
				}
				else if (string(curr->name()) == "creature") {
					creature_list.push_back(curr->value());
				}
				else if (string(curr->name()) == "border") {
					xml_node<>*border = curr->first_node();
					string direction, name;
					if (string(border->name()) == "direction") {
						direction = string(border->value());
						name = string(border->next_sibling()->value());
					} else {
						name = string(border->value());
						direction = string(border->next_sibling()->value());
					}
					border_list.push_back(new Border(direction, name));
				}
				else if (string(curr->name()) == "trigger") {
					Trigger *trigger = new Trigger(curr);
					trigger_list.push_back(trigger);
				}
			}
		}
};

#endif /* ROOM_HPP_ */
