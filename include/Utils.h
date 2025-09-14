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
    bool isValid(std::vector<RouteStep> &r, node **&m, int vehicle_capacity);
    void updateRoute(std::vector<RouteStep> &r, node **&m);
    int custo_total(std::vector<std::vector<RouteStep>> &solution);
};

#endif // H_UTILS_H
