/*
 * Container.hpp
 *
 *  Created on: Dec 9, 2016
 *      Author: xiao81
 */

#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include "header.hpp"
#include "Trigger.hpp"

class Container {
public:
	string name;
	string status;
	string description;
	vector<string> accept_list;
	vector<string> item_list;
	vector<Trigger*> trigger_list;
	Container(xml_node<> *node){
		parse_container(node);
	}
	virtual ~Container(){};

private:
	void parse_container(xml_node<> *node) {
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
			else if (string(curr->name()) == "item") {
				item_list.push_back(curr->value());
			}
			else if (string(curr->name()) == "accept") {
				accept_list.push_back(curr->value());
			}
			else if (string(curr->name()) == "trigger") {
				Trigger *trigger = new Trigger(curr);
				trigger_list.push_back(trigger);
			}
		}
	}


};

#endif /* CONTAINER_HPP_ */
