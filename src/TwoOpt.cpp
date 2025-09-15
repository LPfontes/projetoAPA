#include "../include/TwoOpt.h"

TwoOpt::TwoOpt(node **costMatrix) : costMatrix(costMatrix) {}

bool TwoOpt::run(std::vector<std::vector<RouteStep>> &solution, int vehicle_capacity) {

    bool worked = false;

    for (size_t i = 0; i < solution.size(); ++i)
    {
        int route_cost = (solution)[i][(solution)[i].size() - 1].accumulatedCost;

        if (twoopt_in_route(solution[i], route_cost, vehicle_capacity))
        {
            worked = true;
        }
    }

    return worked;

}

bool TwoOpt::twoopt_in_route(std::vector<RouteStep> &routeSteps, int routeCost, int vehicleCapacity) {

    int bestCost = routeCost;
    int bestI;
    int bestJ;
    int best_init;
    int routeSize = routeSteps.size();

    if(routeSize < 6) {
        return false;
    }

    for(int i = 1; i < routeSize -1; ++i) {
        for(int j = i + 4; j < routeSize -1; ++j) {

            int cost = routeCost - (routeSteps[j].accumulatedCost - routeSteps[i].accumulatedCost);
                      
            for (size_t k = j; k > i; --k) {
                cost += costMatrix[routeSteps[k].stationId][routeSteps[k-1].stationId].cost;
            }         
            

            if(cost < bestCost) {
                //std::cout << "\neh menor: " << cost << " tm " << routeSize  << " valor da rota: " << routeCost << " i: " << i << " j " << j << std::endl;
                
            }
            
        }
    }

    return false;

}