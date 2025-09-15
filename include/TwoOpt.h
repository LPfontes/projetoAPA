#ifndef H_TWOOPT_H
#define H_TWOOPT_H

#include <iostream>
#include <vector>
#include <time.h>
#include "Solution.h"
#include "Node.h"
#include "RouteStep.h"
#include "Utils.h"

class TwoOpt {
public:

    TwoOpt(node** costMatrix);
    bool run(std::vector<std::vector<RouteStep>> &solution, int vehicle_capacity);

private:

    node** costMatrix; 
    bool twoopt_in_route(std::vector<RouteStep> &routeSteps, int routeCost, int vehicleCapacity);

};



#endif // H_TWOOPT_H




