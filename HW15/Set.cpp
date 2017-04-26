/*
 * Set.cpp
 *
 *  Created on: Nov 5, 2016
 *      Author: xiao81
 */

#include "Set.h"
#include <iostream>
using namespace std;

Set::Set(int num){
	this->set[0] = num;
	this->index =0;
}

Set::~Set() {
	// TODO Auto-generated destructor stub
}

Set operator+(int num) {
	for (int i = 0; i < 10; i++) {
		if (this.set[i] == num) {
			return this;
		}
	}
	this.set[s.index++] = num;
	return this;
}

Set operator-(Set s, int num) {
	for (int i = 0; i < 10; i++) {
		if (s.set[i] == 0) {
			return s;
		}
	}
	return s;
}

bool operator&(Set s1, Set s2) {
	for (int i = 0; i < 10; i++) {
		if (s1.set[i] != s2.set[i]) {
			return false;
		}
	}
	return true;
}

Set operator~(Set s) {
	for (int i = 0; i < 10; i++) {
		if (s.set[i] == 0) {
			return s;
		}
	}
	return s;
}

Set operator<<(Set s) {
	for (int i = 0; i < 10; i++) {
		if (s.set[i] == 0) {
			return s;
		}
	}
	return s;
}

