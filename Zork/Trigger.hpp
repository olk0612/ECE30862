/*
 * Trigger.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: xiao81
 */

#ifndef TRIGGER_HPP_
#define TRIGGER_HPP_
#include "header.hpp"
#include "Status.hpp"
#include "Owner.hpp"


class Trigger {
public:
	string type;
	string command;
	vector<string> print_list;
	vector<string> action_list;
	Owner* owner;
	Status* status;
	int count;
	int condition_count;

	Trigger(xml_node<> *node){
		count = 0;
		condition_count =0;
		parse_trigger(node);

	}
	virtual ~Trigger(){};
private:
	void parse_trigger(xml_node<> *node) {
		type = "single";
		for(xml_node<> *curr = node -> first_node(); curr; curr = curr -> next_sibling()) {
			if (string(curr->name()) == "type") {
				type = curr->value();
			}
			if (string(curr->name()) == "command") {
				command = curr->value();
			}
			if (string(curr->name()) == "action") {
				action_list.push_back(curr->value());
			}
			if (string(curr->name()) == "print") {
				print_list.push_back(curr->value());
			}
			if (string(curr->name()) == "condition") {
				condition_count = get_child_count(curr);
				if (condition_count == 2) {
					string object, status_content;
					for(xml_node<> *status_node= curr -> first_node(); status_node; status_node = status_node -> next_sibling()) {
						if (string(status_node->name()) == "object") {
							object = string(status_node->value());
						}else if (string(status_node->name()) == "status") {
							status_content = string(status_node->value());
						}
					}
					status = new Status(object, status_content);

				}
				else if (condition_count == 3) {
					string object, owner_content,has;
					for(xml_node<> *owner_node= curr -> first_node(); owner_node; owner_node = owner_node -> next_sibling()) {

						if (string(owner_node->name()) == "object") {
							object = string(owner_node->value());
						}else if (string(owner_node->name()) == "has") {
							has = string(owner_node->value());
						}else if (string(owner_node->name()) == "owner") {
							owner_content = string(owner_node->value());
						}

					}
					owner = new Owner(object, has, owner_content);

				}
			}
		}
	}

	int get_child_count(xml_node<> *node) {
		int count = 0;
		for (xml_node<> *child = node->first_node(); child ; child = child->next_sibling()) {
			count++;
		}
		return count;
	}
};

#endif /* TRIGGER_HPP_ */
