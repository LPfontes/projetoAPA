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

    Swap(node** m);
    bool run(std::vector<std::vector<RouteStep>> &solution, int vehicle_capacity);

private:

    node** m; 
    bool swap_in_route(std::vector<RouteStep> &r, int route_cost, int vehicle_capacity);

};



#endif // H_SWAP_H





