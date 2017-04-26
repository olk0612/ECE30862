/*
 * Canine.cpp
 *
 *  Created on: Nov 5, 2016
 *      Author: xiao81
 */

#include "Canine.h"
#include <string>
using namespace std;

Canine::Canine(string input) :
	Mammal(4), breed(input) {
}

Canine::~Canine() {

}

string Canine::get_breed(){
	return this->breed;
}

