#ifndef H_REINSERTION_H
#define H_REINSERTION_H

#include <iostream>
#include <vector>
#include <time.h>
#include "Solution.h"
#include "Node.h"
#include "RouteStep.h"
#include "Utils.h"

class ReInsertion {
public:
    ReInsertion(node **costMatrix);
    bool run(std::vector<std::vector<RouteStep>> &solution, int vehicle_capacity);

private:
    node** costMatrix; 
    bool reinsertion_in_route(std::vector<RouteStep> &routeSteps, int routeCost, int vehicleCapacity);
    int calculateReinsertionCost(int routeCost, int i, int j, const std::vector<RouteStep>& routeSteps, node** costMatrix);
};


# endif // H_REINSERTION_H
