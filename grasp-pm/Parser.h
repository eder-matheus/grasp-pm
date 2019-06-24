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
    Parser(const std::string);
    virtual ~Parser();

    int getQtdMachines() const;
    int getQtdTasks() const;

    int getProcTime(int, int) const;
    std::vector<std::vector<int>> getProcTimes() const;
    int getSetupTime(int, int, int) const;
    std::vector<std::vector<std::vector<int>>> getSetupTimes() const;
    int getGijk(int, int, int) const;

    const char *getName() const;
    void writeFile(const std::string) const;

protected:
    const std::string inputFile;
    int m_num;
    int qtdMachines, qtdTasks;
    std::vector<std::vector<int>> procTimes; // [job][machine]
    std::vector<std::vector<std::vector<int>>> setupTimes; // [pred job][succ job][machine]
};

#endif /* PARSER_H */

