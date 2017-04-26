/*
 * Owner.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: xiao81
 */

#ifndef OWNER_HPP_
#define OWNER_HPP_
#include "header.hpp"

class Owner {
public:
	string object;
	string has;
	string owner;
	Owner(string object_input, string has_input, string owner_input) {
		object = object_input;
		has = has_input;
		owner = owner_input;
	};
	virtual ~Owner(){};
};

#endif /* OWNER_HPP_ */
