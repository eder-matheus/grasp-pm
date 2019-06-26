#include "Grasp.h"

Grasp::Grasp(const std::string &inputFile) {
    // Initializing structures
    Parser parser(inputFile);

    numMachines = parser.getQtdMachines();
    numTasks = parser.getQtdTasks();
    procTimes = parser.getProcTimes();
    setupTimes = parser.getSetupTimes();
    tasksPerMachine.resize(numMachines);
} // end method

// -----------------------------------------------------------------------------

Grasp::~Grasp() {
} // end method

// -----------------------------------------------------------------------------

int Grasp::getNumMachines() const {
    return numMachines;
} // end method

// -----------------------------------------------------------------------------

int Grasp::getNumTasks() const {
    return numTasks;
} // end method

// -----------------------------------------------------------------------------

int Grasp::getProcTime(int task, int machine) const {
    return procTimes[task][machine];
} // end method

// -----------------------------------------------------------------------------

int Grasp::getSetupTime(int predTask, int succTask, int machine) const {
    if (predTask == succTask)
        return 0;
    return setupTimes[predTask][succTask][machine];
} // end method

// -----------------------------------------------------------------------------

int Grasp::getTotalTime(int predTask, int succTask, int machine) const {
    return getProcTime(succTask, machine) + getSetupTime(predTask, succTask, machine);
} // end method

// -----------------------------------------------------------------------------

void Grasp::printStructures() {
    std::ofstream output("out.txt", std::ofstream::out);
    if (!output) {
        std::cout << "Error: output file could not be created\n";
        std::abort();
    } // end if

    output << "#?" << '\n' << numMachines << '\n' << numTasks << "\n\n";

    for (int i = 0; i < numTasks; ++i) {
        for (int j = 0; j < numMachines; ++j) {
            output << procTimes[i][j] << ' ';
        } // end for
        output << '\n';
    } // end for
    output << "\n";

    for (int k = 0; k < numMachines; ++k) {
        for (int i = 0; i < numTasks; ++i) {
            for (int j = 0; j < numTasks; ++j) {
                output << setupTimes[i][j][k] << ' ';
            } // end for
            output << "\n";
        } // end for
        output << "\n";
    } // end for

    output.close();
} // end method

// -----------------------------------------------------------------------------

std::vector<std::vector<int>> Grasp::createInitialSolution(long seed) {
    std::vector<int> machines;
    std::vector<int> tasks;
    
    std::vector<std::vector<int>> solution;
    solution.resize(numMachines);
    
    for (int j = 0; j < numTasks; j++)
        tasks.push_back(j);
    for (int k = 0; k < numMachines; k++)
        machines.push_back(k);
    
    while (tasks.size() > 0) {
        std::tuple<int, int, int> bestCandidate = std::make_tuple(-1, -1, 
                                        std::numeric_limits<int>::max());
        for (int machine : machines) {
            for (int task : tasks) {
                if (solution[machine].size() <= 0) {
                    int currCost = getTotalTime(task, task, machine);
                    if (currCost < std::get<2>(bestCandidate)) {
                        bestCandidate = std::make_tuple(task, machine, currCost);
                    }
                } else {
                    int currCost = getTotalTime(solution[machine].back(), task,
                                                machine);
                    if (currCost < std::get<2>(bestCandidate)) {
                        bestCandidate = std::make_tuple(task, machine, currCost);
                    }
                }
            }
        }
                
        solution[std::get<1>(bestCandidate)].push_back(std::get<0>(bestCandidate));
        std::vector<int>::iterator it = std::find(tasks.begin(), tasks.end(), 
                                            std::get<0>(bestCandidate));
        int index = std::distance(tasks.begin(), it);
        tasks.erase(tasks.begin()+index);
    }
    
    return solution;
} // end method

// -----------------------------------------------------------------------------
//int Grasp::getTotalTime(int predTask, int succTask, int machine)
int Grasp::evaluateSolution(const std::vector<int> &solution, int machine) {
    int cost = 0;
    
    for (int i = 0; i < solution.size(); i++) {
        if (i == 0) {
            cost += getTotalTime(solution[i], solution[i], machine);
        } else {
            cost += getTotalTime(solution[i-1], solution[i], machine);
        }
    }

    return cost;
} // end method

// -----------------------------------------------------------------------------

void Grasp::addEliteSolution(const std::pair<std::vector<int>, int> &solution) {
    auto sort = [](std::pair<std::vector<int>, int> s1, 
                   std::pair<std::vector<int>, int> s2) -> bool {
            return s1.second < s2.second;
    };

    if (solution.second < eliteSolutions.back().second) {
        eliteSolutions.pop_back();
        eliteSolutions.push_back(solution);
    } else {
        return;
    }

    std::sort(eliteSolutions.begin(), eliteSolutions.end(), sort);
} // end method

// -----------------------------------------------------------------------------