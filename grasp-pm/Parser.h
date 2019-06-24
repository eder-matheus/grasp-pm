/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.h
 * Author: emrmonteiro
 *
 * Created on June 23, 2019, 8:56 PM
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

#ifndef PARSER_H
#define PARSER_H

class Parser {
public:
   Parser(const char *fname);
   virtual ~Parser();

   int getNumMachines() const;
   int getNumJobs() const;

   int getProcTime(int job, int machine) const;
   int getSetupTime(int predJob, int succJob, int machine) const;
   int getGijk(int predJob, int succJob, int machine) const;

   const char *getName() const;
   void writeFile(const char *fname) const;

protected:
   const std::string m_name;
   int m_num;
   int m_numMachines, m_numJobs;
   std::vector <std::vector <int> > m_procTimes; // [job][machine]
   std::vector <std::vector <std::vector <int> > > m_setupTimes; // [pred job][succ job][machine]
};

#endif /* PARSER_H */

