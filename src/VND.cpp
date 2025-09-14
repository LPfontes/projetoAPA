#include "../include/VND.h"
#include <algorithm>
#include <numeric>

VND::VND() {}

VND::~VND() {}

void VND::run(std::vector<int>& solution) {
    int bestCost = evaluate(solution);
    bool improved = true;

    while (improved) {
        improved = false;

        // Neighborhood 1
        std::vector<int> temp1 = solution;
        neighborhood1(temp1);
        int cost1 = evaluate(temp1);
        if (cost1 < bestCost) {
            solution = temp1;
            bestCost = cost1;
            improved = true;
            continue;
        }

        // Neighborhood 2
        std::vector<int> temp2 = solution;
        neighborhood2(temp2);
        int cost2 = evaluate(temp2);
        if (cost2 < bestCost) {
            solution = temp2;
            bestCost = cost2;
            improved = true;
            continue;
        }

        // Neighborhood 3
        std::vector<int> temp3 = solution;
        neighborhood3(temp3);
        int cost3 = evaluate(temp3);
        if (cost3 < bestCost) {
            solution = temp3;
            bestCost = cost3;
            improved = true;
            continue;
        }
    }
}

void VND::neighborhood1(std::vector<int>& solution) {
    // Swap two random elements
    if (solution.size() < 2) return;
    std::swap(solution[0], solution[1]);
}

void VND::neighborhood2(std::vector<int>& solution) {
    // Reverse the solution
    std::reverse(solution.begin(), solution.end());
}

void VND::neighborhood3(std::vector<int>& solution) {
    // Rotate left by one
    if (solution.size() < 2) return;
    std::rotate(solution.begin(), solution.begin() + 1, solution.end());
}

int VND::evaluate(const std::vector<int>& solution) {
    
}