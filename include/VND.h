#ifndef H_VND_H
#define H_VND_H

#include <iostream>
#include <vector>
#include <time.h>
#include "Solution.h"
#include "Node.h"
#include "RouteStep.h"
#include "Swap.h"
#include "Utils.h"

class VND {
public:
    
    void vnd(std::vector<std::vector<RouteStep>> &solution, node** &matrix, int total_cost, int vehicle_capacity);

};

#endif // H_VND_H





