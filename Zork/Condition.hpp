/*
 * Condtion.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: xiao81
 */

#ifndef CONDITION_HPP_
#define CONDITION_HPP_
#include "header.hpp"

class Condition {
public:
	string object;
	string status;
	Condition(string object_input, string status_input){
		object = object_input;
		status = status_input;
	};
	virtual ~Condition(){};
};

#endif /* CONDITION_HPP_ */
