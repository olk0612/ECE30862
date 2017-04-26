#include "Mammal.h"

Mammal::Mammal(int input) :
	legs(input) {
}

Mammal::~Mammal( ) { }

int Mammal::get_legs() {
	return this->legs;
}
