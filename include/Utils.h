#ifndef H_UTILS_H
#define H_UTILS_H

#include <iostream>
#include <vector>
#include <time.h>
#include "Solution.h"
#include "Node.h"
#include "RouteStep.h"

class Utils
{
public:
    int isValid(std::vector<RouteStep> &routeSteps, node **&costMatrix, int vehicle_capacity);
    void updateRoute(std::vector<RouteStep> &routeSteps, node **&costMatrix);
    int custoTotal(std::vector<std::vector<RouteStep>> &solution);
};

#endif // H_UTILS_H
