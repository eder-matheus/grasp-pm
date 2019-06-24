/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: emrmonteiro
 *
 * Created on June 23, 2019, 8:55 PM
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

#include "Parser.h"

int main(int argc, char **argv) {
   if (argc != 2) {
      std::cout << "Usage: " << argv[0] << " <instance file>\n";
      return -1;
   }

   Parser inst(argv[1]);
   inst.writeFile("pmsp.txt");

   return 0;
}


