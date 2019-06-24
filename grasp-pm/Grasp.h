#ifndef GRASP_H
#define GRASP_H

#include "Parser.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

class Grasp {
public:
    Grasp(const std::string);
    Grasp(const Grasp& orig);
    virtual ~Grasp();
    
    int getMachines() const;
    int getTasks() const;

    int getProcTime(int, int) const;
    int getSetupTime(int, int, int) const;
    
    void printStructures();
    
private:
    // attributes
    int machines;
    int tasks;
    std::vector<std::vector<int>> procTimes;
    std::vector<std::vector<std::vector<int>>> setupTimes;

    // methods
    int getTotalTime(int, int, int) const;
};

#endif /* GRASP_H */

