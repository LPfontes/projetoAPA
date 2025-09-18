#include "../include/ReInsertion.h"
#include "../include/Utils.h"

ReInsertion::ReInsertion(node** costMatrix) : costMatrix(costMatrix) {};

bool ReInsertion::run(std::vector<std::vector<RouteStep>> &solution, int vehicle_capacity) {
    bool worked = false;

    for (size_t i = 0; i < solution.size(); ++i)
    {
        int route_cost = solution[i].back().accumulatedCost;

        if (reinsertion_in_route(solution[i], route_cost, vehicle_capacity))
        {
            worked = true;
            
        }
    }

    return worked;
}

bool ReInsertion::reinsertion_in_route(std::vector<RouteStep> &routeSteps, int routeCost, int vehicleCapacity) {
    
    bool worked = false;
    int bestCost = routeCost;
    int routeSize = routeSteps.size();
    std::vector<RouteStep> bestRoute;
    Utils utils;

    if (routeSize < 4) { 
        return false;
    }

    for (int i=1; i < routeSize-1; i++) {
        int routCostAfterRemoval = routeCost 
                                   -costMatrix[routeSteps[i-1].stationId][routeSteps[i].stationId].cost 
                                   -costMatrix[routeSteps[i].stationId][routeSteps[i+1].stationId].cost 
                                   +costMatrix[routeSteps[i-1].stationId][routeSteps[i+1].stationId].cost;
            
        for (int j=1; j < routeSize-1; j++) {
            
            if (j == i) continue; // Solução original

            // Lógica 
            int routCostAfterInsertion = routCostAfterRemoval
                - costMatrix[routeSteps[j-1].stationId][routeSteps[j].stationId].cost
                + costMatrix[routeSteps[j-1].stationId][routeSteps[i].stationId].cost
                + costMatrix[routeSteps[i].stationId][routeSteps[j].stationId].cost;

            if (routCostAfterInsertion < bestCost) {
                // testar rota com inserção
                std::vector<RouteStep> tempRoute = routeSteps;
                RouteStep nodeToMove = tempRoute[i];
                tempRoute.erase(tempRoute.begin() + i);

                int insertionIndex = j;

                if (i < j) {
                    insertionIndex--; // ajuste pq removemos antes
                }

                tempRoute.insert(tempRoute.begin() + insertionIndex, nodeToMove);
                utils.updateRoute(tempRoute, costMatrix);
                
                if (utils.isValid(tempRoute, costMatrix, vehicleCapacity) != -1) {
                    if (tempRoute.back().accumulatedCost < routeSteps.back().accumulatedCost) {
                        bestRoute = tempRoute;
                        bestCost = routCostAfterInsertion;
                        worked = true;
                    }
                }
            }
        }
    }

    if (worked) {
        routeSteps = bestRoute;
        utils.updateRoute(routeSteps, costMatrix);

        return true;
    }

    return false;
}