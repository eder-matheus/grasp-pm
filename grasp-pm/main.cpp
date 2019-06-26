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

    std::vector<std::vector<int>> Si;
    Si = grasp.createInitialSolution();

    for (int i = 0; i < Si.size(); i++) {
        int cost = 0;
        cost = grasp.evaluateSolution(Si[i], i);
    }

    int noImprovement = 0;
    std::vector<std::vector<int>> partialSolution;
    std::vector<std::vector<int>> localSearchSol;
    int lastCost = std::numeric_limits<int>::max();
    int counter = 10000;
    do {
        partialSolution = grasp.greedRandomizedSolution(alpha, seed*counter);
            
        int worstCost;
        int worstCostPartial = 0;
        int worstCostLocal = 0;
        for (int i = 0; i < partialSolution.size(); i++) {
            int machineCost = grasp.evaluateSolution(partialSolution[i], i);
            if (machineCost > worstCostPartial)
                worstCostPartial = machineCost;
        }
        
        localSearchSol = grasp.localSearch(partialSolution, seed);
        
        for (int i = 0; i < localSearchSol.size(); i++) {
            int machineCost = grasp.evaluateSolution(localSearchSol[i], i);
            if (machineCost > worstCostLocal)
                worstCostLocal = machineCost;
        }
        
        if (worstCostLocal <= worstCostPartial) {
            worstCost = worstCostLocal;
            grasp.addEliteSolution(std::make_pair(localSearchSol, worstCost));
        } else {
            worstCost = worstCostPartial;
            grasp.addEliteSolution(std::make_pair(partialSolution, worstCost));
        }
        
        if (worstCost < lastCost) {
            lastCost = worstCost;
        } else {
            noImprovement++;
        }
        
        counter--;
    } while (noImprovement < 10000);
    
    std::vector<std::pair<std::vector<std::vector<int>>, int>> elite = grasp.getEliteSolutions();
    std::cout << "Final cost: " << elite.back().second << "\n";

    return 0;
}