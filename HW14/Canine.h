/*
 * Canine.h
 *
 *  Created on: Nov 5, 2016
 *      Author: xiao81
 */

#ifndef CANINE_H_
#define CANINE_H_
#include <string>
#include "Mammal.h"
using namespace std;

class Canine: public Mammal{
private:
	string breed;
public:
	Canine(string input);
	virtual ~Canine();
	virtual string get_breed();
};

#endif /* CANINE_H_ */

