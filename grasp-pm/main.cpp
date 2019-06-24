#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include "Grasp.h"

int main(int argc, char **argv) {
   if (argc != 3) {
      std::cout << "Usage: " << argv[0] << " <instance file>\n";
      return -1;
   }

   char *p;
   long seed = strtol(argv[2], &p, 10);
   
   Grasp grasp(argv[1]);
   grasp.printStructures();
   std::vector<int> Si;
   Si = grasp.createInitialSolution(seed);

   return 0;
}


