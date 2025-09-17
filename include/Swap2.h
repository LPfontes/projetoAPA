#ifndef H_SWAP2_H
#define H_SWAP2_H

#include <iostream>
#include <vector>
#include <time.h>
#include "Solution.h"
#include "Node.h"
#include "RouteStep.h"
#include "Utils.h"

class Swap2 {
public:

    Swap2(node** costMatrix);
    bool run(std::vector<std::vector<RouteStep>> &solution, int vehicleCapacity, int total);

private:

    node** costMatrix; 
    int calculateSwapCost(int solutionCost, int i, int j, int k, int l,
                             std::vector<std::vector<RouteStep>> &solution,
                             node **costMatrix);
};



#endif // H_SWAP2_H





