/*
 * Item.hpp
 *
 *  Created on: Dec 9, 2016
 *      Author: xiao81
 */

#ifndef ITEM_HPP_
#define ITEM_HPP_

#include "header.hpp"
#include "TurnOn.hpp"
#include "Trigger.hpp"

class Item {
public:
	string name;
	string status;
	string description;
	string writing;
	TurnOn* turn_on;
	vector<Trigger*> trigger_list;
	Item(xml_node<> *node){
		parse_item(node);
	}
	virtual ~Item(){};

private:
	void parse_item(xml_node<> *node) {
		for(xml_node<> *curr = node -> first_node(); curr; curr = curr -> next_sibling()) {
			turn_on = NULL;
			if (string(curr->name()) == "name") {
				name = curr->value();
			}
			else if (string(curr->name()) == "status") {
				status = curr->value();
			}
			else if (string(curr->name()) == "description") {
				description = curr->value();
			}
			else if (string(curr->name()) == "writing") {
				writing = curr->value();
			}
			else if (string(curr->name()) == "turnon") {
				xml_node<>*turnon = curr->first_node();
				string print = string(turnon->value());
				string action = string(turnon->next_sibling()->value());
				turn_on = new TurnOn(print, action);
			}
			else if (string(curr->name()) == "trigger") {
				Trigger *trigger = new Trigger(curr);
				trigger_list.push_back(trigger);
			}
		}
	}


};

#endif /* ITEM_HPP_ */
