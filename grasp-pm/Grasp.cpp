#include "Grasp.h"

Grasp::Grasp(const std::string &inputFile) {
    // Initializing structures
    Parser parser(inputFile);
    
    machines = parser.getQtdMachines();
    tasks = parser.getQtdTasks();
    procTimes = parser.getProcTimes();
    setupTimes = parser.getSetupTimes();
}

Grasp::~Grasp() {
}

int Grasp::getMachines() const {
   return machines;
}

int Grasp::getTasks() const {
   return tasks;
}

int Grasp::getProcTime(int task, int machine) const {
   return procTimes[task][machine];
}

int Grasp::getSetupTime(int predTask, int succTask, int machine) const {
   return setupTimes[predTask][succTask][machine];
}

int Grasp::getTotalTime(int predTask, int succTask, int machine) const {
    return getProcTime(succTask, machine) + getSetupTime(predTask, succTask, machine);
}

void Grasp::printStructures() {
    std::ofstream output("out.txt", std::ofstream::out);
   if (!output) {
      std::cout << "Error: output file could not be created\n";
      std::abort();
   }

   output << "#?" << '\n' << machines << '\n' << tasks << "\n\n";

   for (int i = 0; i < tasks; ++i) {
      for (int j = 0; j < machines; ++j) {
         output << procTimes[i][j] << ' ';
      }
      output << '\n';
   }
   output << "\n";

   for (int k = 0; k < machines; ++k) {
      for (int i = 0; i < tasks; ++i) {
         for (int j = 0; j < tasks; ++j) {
            output << setupTimes[i][j][k] << ' ';
         }
         output << "\n";
      }
      output << "\n";
   }
   
   output.close();
}

std::vector<int> Grasp::createInitialSolution(long seed) {
    // engine to generate the pseudo-random numbers
    std::default_random_engine dre(seed);
    // distribution of the pseudo-random numbers
    // 
    std::uniform_int_distribution<int> dist(0, (machines-1));
    
    std::vector<int> solution(tasks);
    std::generate(solution.begin(), solution.end(), [&]{ return dist(dre);});
    
    return solution;
}