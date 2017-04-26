#include <string>
#include <iostream>
#include "Mammal.h"
#include "Canine.h"
#include "Pet.h"
using namespace std;

int main(void) {

	Mammal m(4);
	cout << "Mammal:" <<endl;
	cout << m.get_legs() <<endl;
	Canine c("Husky");
	cout << "Canine:" <<endl;
	cout << c.Mammal::get_legs()<<endl;
	cout << c.get_breed()<<endl;
	Pet p("Husky");
	cout << "Pet:" <<endl;
	cout << c.Mammal::get_legs()<<endl;
	cout << p.get_breed()<<endl;
	return 0;
}
