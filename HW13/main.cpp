#include "Base.h"
#include "PrivDerived.h"
#include "ProtDerived.h"
#include "PublicDerived.h"
#include "dPriv.h"
#include "dProt.h"
#include "dPublic.h"
#include <iostream>
#include <string>
using namespace std;

int main(void) {

   Mammal m = new Mammal(4);

   cout << "b" << endl;

   return 0;
}
