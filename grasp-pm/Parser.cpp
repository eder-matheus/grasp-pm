/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.cpp
 * Author: emrmonteiro
 * 
 * Created on June 23, 2019, 8:57 PM
 */

#include "Parser.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

Parser::Parser(const char* fname): m_name(fname) {
    std::cout << "File name: " << fname << "\n";
   std::ifstream fid(fname);
   if (!fid) {
      std::cout << "Instance file could not be open to read.\n";
      std::abort();
   }

   fid >> m_num >> m_numMachines >> m_numJobs;

   m_procTimes.resize(m_numJobs);
   m_setupTimes.resize(m_numJobs);
   for (int i = 0; i < m_numJobs; ++i) {
      m_procTimes[i].resize(m_numMachines, std::numeric_limits<int>::max());
      m_setupTimes[i].resize(m_numJobs);
      for (int j = 0; j < m_numJobs; ++j) {
         m_setupTimes[i][j].resize(m_numMachines, std::numeric_limits<int>::max());
      }
   }

   for (int i = 0; i < m_numJobs; ++i) {
      for (int j = 0; j < m_numMachines; ++j) {
         fid >> m_procTimes[i][j];
      }
   }

   for (int k = 0; k < m_numMachines; ++k) {
      for (int i = 0; i < m_numJobs; ++i) {
         for (int j = 0; j < m_numJobs; ++j) {
            fid >> m_setupTimes[i][j][k];
         }
      }
   }

}

Parser::~Parser() {
   // Empty
}

int Parser::getNumMachines() const {
   return m_numMachines;
}

int Parser::getNumJobs() const {
   return m_numJobs;
}

int Parser::getProcTime(int job, int machine) const {
   return m_procTimes[job][machine];
}

int Parser::getSetupTime(int predJob, int succJob, int machine) const {
   return m_setupTimes[predJob][succJob][machine];
}

int Parser::getGijk(int predJob, int succJob, int machine) const {
   return getProcTime(succJob, machine) + getSetupTime(predJob, succJob, machine);
}

const char *Parser::getName() const {
   return m_name.c_str();
}

void Parser::writeFile(const char* fname) const {
   std::ofstream fid("out.txt", std::ofstream::out);
   if (!fid) {
      std::cout << "Output file could not be open to write.\n";
      std::abort();
   }

   fid << m_num << '\n' << m_numMachines << '\n' << m_numJobs << "\n\n";

   for (int i = 0; i < m_numJobs; ++i) {
      for (int j = 0; j < m_numMachines; ++j) {
         fid << m_procTimes[i][j] << ' ';
      }
      fid << '\n';
   }
   fid << "\n";

   for (int k = 0; k < m_numMachines; ++k) {
      for (int i = 0; i < m_numJobs; ++i) {
         for (int j = 0; j < m_numJobs; ++j) {
            fid << m_setupTimes[i][j][k] << ' ';
         }
         fid << "\n";
      }
      fid << "\n";
   }
   
   fid.close();
}