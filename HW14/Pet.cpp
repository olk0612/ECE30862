/*
 * Pet.cpp
 *
 *  Created on: Nov 5, 2016
 *      Author: xiao81
 */

#include "Pet.h"


Pet::Pet(string input):
	Canine(input) {
}

Pet::~Pet() {
}

string Pet::get_breed(){
	return "AKC: " + Canine::get_breed();
}
