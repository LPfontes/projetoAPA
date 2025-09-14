#ifndef H_SWAP_H
#define H_SWAP_H

#include <iostream>
#include <vector>
#include <time.h>
#include "Solution.h"
#include "Node.h"
#include "RouteStep.h"
#include "Utils.h"

class Swap {
public:

    Swap(node** costMatrix);
    bool run(std::vector<std::vector<RouteStep>> &solution, int vehicle_capacity);

private:

    node** costMatrix; 
    bool swap_in_route(std::vector<RouteStep> &routeSteps, int routeCost, int vehicleCapacity);

};



#endif // H_SWAP_H





