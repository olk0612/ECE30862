#ifndef MAMMAL_H
#define MAMMAL_H
#include <iostream>
#include <string>
using namespace std;

class Mammal {
	private:
		int legs;
	public:
		int get_legs();
		Mammal(int input);
		virtual ~Mammal( );
};

#endif
