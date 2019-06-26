#ifndef GRASP_H
#define GRASP_H

#include "Parser.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <tuple>
#include <utility>

#define ELITE_TOTAL 10

class Grasp {
public:
    Grasp(const std::string &);
    virtual ~Grasp();
    
    int getNumMachines() const;
    int getNumTasks() const;

    int getProcTime(int, int) const;
    int getSetupTime(int, int, int) const;
    
    int getTotalTime(int, int, int) const;
    
    std::vector<std::pair<std::vector<std::vector<int>>, int>> getEliteSolutions()
    { return eliteSolutions; }
    
    void printStructures();
    
    std::vector<std::vector<int>> createInitialSolution();
    
    std::vector<std::vector<int>> greedRandomizedSolution(float alpha, long seed);
    
    std::vector<std::vector<int>> localSearch(const std::vector<std::vector<int>> &, long);
    
    int selectWorstTimeTask(const std::vector<int> &, int);
    
    int evaluateSolution(const std::vector<int> &, int);
    
    void addEliteSolution(const std::pair<std::vector<std::vector<int>>, int> &);
    
private:
    int numMachines;
    int numTasks;
    std::vector<std::vector<int>> tasksPerMachine;
    std::vector<std::vector<int>> procTimes;
    std::vector<std::vector<std::vector<int>>> setupTimes;
    std::vector<std::pair<std::vector<std::vector<int>>, int>> eliteSolutions;
};

#endif /* GRASP_H */

