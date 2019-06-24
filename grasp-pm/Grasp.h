#ifndef GRASP_H
#define GRASP_H

#include "Parser.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <utility>

#define ELITE_TOTAL 10

class Grasp {
public:
    Grasp(const std::string &);
    virtual ~Grasp();
    
    int getMachines() const;
    int getTasks() const;

    int getProcTime(int, int) const;
    int getSetupTime(int, int, int) const;
    
    int getTotalTime(int, int, int) const;
    
    void printStructures();
    
    std::vector<int> createInitialSolution(long);
    
    int evaluateSolution(const std::vector<int> &);
    
    void addEliteSolution(const std::pair<std::vector<int>, int> &);
    
private:
    // attributes
    int machines;
    int tasks;
    std::vector<std::vector<int>> procTimes;
    std::vector<std::vector<std::vector<int>>> setupTimes;
    std::vector<std::pair<std::vector<int>, int>> eliteSolutions;
};

#endif /* GRASP_H */

