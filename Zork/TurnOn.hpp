/*
 * TurnOn.hpp
 *
 *  Created on: Dec 9, 2016
 *      Author: xiao81
 */

#ifndef TURNON_HPP_
#define TURNON_HPP_
#include "header.hpp"

class TurnOn {
public:
	string print;
	string action;
	TurnOn(string print_input, string action_input){
		print = print_input;
		action = action_input;
	}
	virtual ~TurnOn(){};
};

#endif /* TURNON_HPP_ */
