/*
 * Status.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: xiao81
 */

#ifndef STATUS_HPP_
#define STATUS_HPP_
#include "header.hpp"

class Status {
public:
	string object;
	string status;
	Status(string object_input, string status_input){
		object = object_input;
		status = status_input;
	};
	virtual ~Status(){};
};

#endif /* STATUS_HPP_*/
