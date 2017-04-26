/*
 * Border.hpp
 *
 *  Created on: Dec 9, 2016
 *      Author: xiao81
 */

#ifndef BORDER_HPP_
#define BORDER_HPP_
#include "header.hpp"

class Border {
public:
	string direction;
	string name;
	Border(string direction_input, string name_input){
		direction = direction_input[0];
		name = name_input;
	}
	virtual ~Border(){};
};

#endif /* BORDER_HPP_ */
