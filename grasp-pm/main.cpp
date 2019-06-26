#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include "Grasp.h"

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <instance file> <alpha> <seed>\n";
        return -1;
    }

    char *p;
    char *q;
    float alpha = strtol(argv[2], &p, 10);
    long seed = strtol(argv[3], &q, 10);

    alpha /= 100;

    Grasp grasp(argv[1]);
    grasp.printStructures();
    std::vector<std::vector<int>> Si;
    std::cout << "-Initial solution\n";
    Si = grasp.createInitialSolution();

    for (int i = 0; i < Si.size(); i++) {
        int cost = 0;
        cost = grasp.evaluateSolution(Si[i], i);
        std::cout << "--Machine " << i << ": \n";
        std::cout << "---Cost " << cost << "\n";
        for (int j = 0; j < Si[i].size(); j++) {
            std::cout << "\t Task " << Si[i][j] << "\n";
        }
    }

    int counter = 0;
    std::vector<std::vector<int>> partialSolution;
    do {
        std::cout << "\n ----------------------------------\n";
        std::cout << "-Solution #" << counter << "\n";
        partialSolution = grasp.greedRandomizedSolution(alpha, seed*counter);

        for (int i = 0; i < partialSolution.size(); i++) {
            int cost = 0;
            cost = grasp.evaluateSolution(partialSolution[i], i);
            std::cout << "--Machine " << i << ": \n";
            std::cout << "---Cost " << cost << "\n";
            for (int j = 0; j < partialSolution[i].size(); j++) {
                std::cout << "\t Task " << partialSolution[i][j] << "\n";
            }
        }
        counter++;
    } while (counter < 5);

    return 0;
}


