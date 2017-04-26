/*
 * Trigger.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: xiao81
 */

#ifndef ATTACK_HPP_
#define ATTACK_HPP_
#include "header.hpp"
#include "Condition.hpp"

class Attack {
public:
	string print;
	Condition* condition;
	vector<string> action_list;
	Attack(xml_node<> *node){
		parse_attack(node);
	};
	virtual ~Attack(){};
private:
	void parse_attack(xml_node<> *node) {
		for(xml_node<> *curr = node -> first_node(); curr; curr = curr -> next_sibling()) {
			if (string(curr->name()) == "condition") {
				xml_node<>*condition_node = curr->first_node();
				string object,status;
				if(string(condition_node->name())=="object") {
					object = string(condition_node->value());
					status = string(condition_node->next_sibling()->value());
				} else {
					status = string(condition_node->value());
					object = string(condition_node->next_sibling()->value());
				}
				condition = new Condition(object, status);
			}
			else if (string(curr->name()) == "print") {
				print = curr->value();
			}
			else if (string(curr->name()) == "action") {
				action_list.push_back(curr->value());
			}
		}
	}
};

#endif /* TRIGGER_HPP_ */
