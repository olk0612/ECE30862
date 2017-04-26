/*
 * Pet.h
 *
 *  Created on: Nov 5, 2016
 *      Author: xiao81
 */

#ifndef PET_H_
#define PET_H_
#include <string>
#include "Canine.h"

class Pet: public Canine {
public:
	Pet(string input);
	virtual ~Pet();
	virtual string get_breed();
};

#endif /* PET_H_ */
