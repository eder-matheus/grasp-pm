#include "Grasp.h"

Grasp::Grasp(const std::string &inputFile) {
    // Initializing structures
    Parser parser(inputFile);

    machines = parser.getQtdMachines();
    tasks = parser.getQtdTasks();
    procTimes = parser.getProcTimes();
    setupTimes = parser.getSetupTimes();
} // end method

// -----------------------------------------------------------------------------

Grasp::~Grasp() {
} // end method

// -----------------------------------------------------------------------------

int Grasp::getMachines() const {
    return machines;
} // end method

// -----------------------------------------------------------------------------

int Grasp::getTasks() const {
    return tasks;
} // end method

// -----------------------------------------------------------------------------

int Grasp::getProcTime(int task, int machine) const {
    return procTimes[task][machine];
} // end method

// -----------------------------------------------------------------------------

int Grasp::getSetupTime(int predTask, int succTask, int machine) const {
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

    output << "#?" << '\n' << machines << '\n' << tasks << "\n\n";

    for (int i = 0; i < tasks; ++i) {
        for (int j = 0; j < machines; ++j) {
            output << procTimes[i][j] << ' ';
        } // end for
        output << '\n';
    } // end for
    output << "\n";

    for (int k = 0; k < machines; ++k) {
        for (int i = 0; i < tasks; ++i) {
            for (int j = 0; j < tasks; ++j) {
                output << setupTimes[i][j][k] << ' ';
            } // end for
            output << "\n";
        } // end for
        output << "\n";
    } // end for

    output.close();
} // end method

// -----------------------------------------------------------------------------

std::vector<int> Grasp::createInitialSolution(long seed) {
    // engine to generate the pseudo-random numbers
    std::default_random_engine engine(seed);
    // distribution of the pseudo-random numbers
    std::uniform_int_distribution<int> dist(0, (machines - 1));

    std::vector<int> solution(tasks);
    std::generate(solution.begin(), solution.end(), [&] {
        return dist(engine);
    });

    std::cout << "Solution size: " << solution.size() << "\n";
    std::cout << "{";
    for (int s : solution) {
        std::cout << s << ", ";
    }

    std::cout << "}\n";

    // a solution is a vector of machines, where each position (idx) refers to
    // a task
    return solution;
} // end method

// -----------------------------------------------------------------------------

int Grasp::evaluateSolution(const std::vector<int> &solution) {
    int cost = 0;

    for (int i = 0; i < solution.size(); i++) {
        if (i == 0) {
            cost += getTotalTime(i, i, solution[i]);
        } else {
            cost += getTotalTime(i - 1, i, solution[i]);
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
    }

    std::sort(eliteSolutions.begin(), eliteSolutions.end(), sort);
} // end method

// -----------------------------------------------------------------------------