/*
 * Creature.hpp
 *
 *  Created on: Dec 9, 2016
 *      Author: xiao81
 */

#ifndef CREATURE_HPP_
#define CREATURE_HPP_

#include "header.hpp"
#include "Trigger.hpp"
#include "Attack.hpp"

class Creature {
public:
	string name;
	string status;
	string description;
	vector<string> vulnerability_list;
	Attack *attack;
	vector<Trigger*> trigger_list;

	Creature(xml_node<> *node){
		parse_creature(node);
	}
	virtual ~Creature(){};
private:
	void parse_creature(xml_node<> *node) {
			for(xml_node<> *curr = node -> first_node(); curr; curr = curr -> next_sibling()) {
				if (string(curr->name()) == "name") {
					name = curr->value();
				}
				else if (string(curr->name()) == "status") {
					status = curr->value();
				}
				else if (string(curr->name()) == "description") {
					description = curr->value();
				}
				else if (string(curr->name()) == "vulnerability") {
					vulnerability_list.push_back(curr->value());
				}
				else if (string(curr->name()) == "attack") {
					attack = new Attack(curr);
				}
				else if (string(curr->name()) == "trigger") {
					Trigger *trigger = new Trigger(curr);
					trigger_list.push_back(trigger);
				}
			}
		}
};

#endif /* CREATURE_HPP_ */
