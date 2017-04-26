/*
 * Set.h
 *
 *  Created on: Nov 5, 2016
 *      Author: xiao81
 */

#ifndef SET_H_
#define SET_H_

class Set {
public:
	Set();
	Set(int num);
	virtual ~Set();
	int set[10];
	int index;
	Set operator+(int num);
	Set operator-(int num);
	Set operator&(Set s);
	Set operator~();
	Set operator<<(Set s);
	Set operator/(Set s);
};

#endif /* SET_H_ */
