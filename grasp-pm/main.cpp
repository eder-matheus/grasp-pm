#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

#include "Grasp.h"

int main(int argc, char **argv) {
   if (argc != 2) {
      std::cout << "Usage: " << argv[0] << " <instance file>\n";
      return -1;
   }

   Grasp grasp(argv[1]);
   grasp.printStructures();

   return 0;
}


