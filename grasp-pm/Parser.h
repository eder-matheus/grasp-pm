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
    Parser(const std::string &);
    virtual ~Parser();

    int getQtdMachines() const; // Number of machines available to run the tasks
    int getQtdTasks() const; // Number of tasks for process

    // Get the time of process of a task in a machine
    int getProcTime(int, int) const;
    // Get the vectors with all process times
    std::vector<std::vector<int>> getProcTimes() const;
    // Get the time of setup of a task in a machine, with another task preceding it
    int getSetupTime(int, int, int) const;
    // Get the matrix of setup times for all tasks in all machines
    std::vector<std::vector<std::vector<int>>> getSetupTimes() const;

protected:
    const std::string inputFile;
    int m_num;
    int qtdMachines, qtdTasks;
    std::vector<std::vector<int>> procTimes; // [job][machine]
    std::vector<std::vector<std::vector<int>>> setupTimes; // [pred job][succ job][machine]
};

#endif /* PARSER_H */

