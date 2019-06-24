#include "Parser.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

Parser::Parser(const std::string &fileName): inputFile(fileName) {
    std::cout << "File name: " << fileName << "\n";
   std::ifstream input(fileName);
   if (!input) {
      std::cout << "Error: input file could not be open\n";
      std::abort();
   } // end if

   input >> m_num >> qtdMachines >> qtdTasks;

   procTimes.resize(qtdTasks);
   setupTimes.resize(qtdTasks);
   for (int i = 0; i < qtdTasks; ++i) {
      procTimes[i].resize(qtdMachines, std::numeric_limits<int>::max());
      setupTimes[i].resize(qtdTasks);
      for (int j = 0; j < qtdTasks; ++j) {
         setupTimes[i][j].resize(qtdMachines, std::numeric_limits<int>::max());
      } // end if
   } // end if

   for (int i = 0; i < qtdTasks; ++i) {
      for (int j = 0; j < qtdMachines; ++j) {
         input >> procTimes[i][j];
      } // end if
   } // end if

   for (int k = 0; k < qtdMachines; ++k) {
      for (int i = 0; i < qtdTasks; ++i) {
         for (int j = 0; j < qtdTasks; ++j) {
            input >> setupTimes[i][j][k];
         } // end if
      } // end if
   } // end if
} // end method

// -----------------------------------------------------------------------------

Parser::~Parser() {
   // Empty
} // end method

// -----------------------------------------------------------------------------

int Parser::getQtdMachines() const {
   return qtdMachines;
} // end method

// -----------------------------------------------------------------------------

int Parser::getQtdTasks() const {
   return qtdTasks;
} // end method

// -----------------------------------------------------------------------------

int Parser::getProcTime(int task, int machine) const {
   return procTimes[task][machine];
} // end method

// -----------------------------------------------------------------------------

std::vector<std::vector<int>> Parser::getProcTimes() const {
    return procTimes;
} // end method

// -----------------------------------------------------------------------------

int Parser::getSetupTime(int predTask, int succTask, int machine) const {
   return setupTimes[predTask][succTask][machine];
} // end method

// -----------------------------------------------------------------------------

std::vector<std::vector<std::vector<int>>> Parser::getSetupTimes() const {
    return setupTimes;
} // end method

// -----------------------------------------------------------------------------