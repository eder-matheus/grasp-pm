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
   std::vector<std::vector<int>> Si;
   std::cout << "Initial solution\n";
   Si = grasp.createInitialSolution(seed);
   
   for (int i = 0; i < Si.size(); i++) {
       int cost = 0;
       cost = grasp.evaluateSolution(Si[i], i);
       std::cout << "Machine " << i << ": \n";
       std::cout << "Cost " << cost << "\n";
       for (int j = 0; j < Si[i].size(); j++) {
           std::cout << "\t Task " << Si[i][j] << "\n";
       }
   }

   return 0;
}


