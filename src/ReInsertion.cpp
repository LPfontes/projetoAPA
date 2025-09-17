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
    
    int bestCost = routeCost;
    int bestI = -1;
    int bestJ = -1;
    int routeSize = routeSteps.size();
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
            int routCostAfterInsertion;

            if (j == i) continue; // Solução original

            // Inserção anterior de i
            if (i < j) {
                routCostAfterInsertion = routCostAfterRemoval 
                                   - costMatrix[routeSteps[j-1].stationId][routeSteps[j].stationId].cost 
                                   + costMatrix[routeSteps[j-1].stationId][routeSteps[i].stationId].cost 
                                   + costMatrix[routeSteps[i].stationId][routeSteps[j].stationId].cost;
            } 
            // Inserição posterior de i
            else {
                routCostAfterInsertion = routCostAfterRemoval
                                   - costMatrix[routeSteps[j].stationId][routeSteps[j+1].stationId].cost 
                                   + costMatrix[routeSteps[j].stationId][routeSteps[i].stationId].cost
                                   + costMatrix[routeSteps[i].stationId][routeSteps[j+1].stationId].cost;
            }

            if (routCostAfterInsertion < bestCost) {
                // Fizemos um meio termo entre melhor rota viável e eficiencia
                std::vector<RouteStep> tempRoute = routeSteps;

                tempRoute.erase(tempRoute.begin() + i);

                int insertionIndex = j;
                if (bestI < bestJ) {
                    insertionIndex--;
                }

                if (utils.isValid(tempRoute, costMatrix, vehicleCapacity) != -1) {
                    bestCost = routCostAfterInsertion;
                    bestI = i;
                    bestJ = j;
                }
            }
        }
    }

    if (bestI != -1) {
        RouteStep nodeToMove = routeSteps[bestI];
        routeSteps.erase(routeSteps.begin() + bestI);
        int insertionIndex = bestJ;

        if( bestI < bestJ) {
            insertionIndex--;
        }
        routeSteps.insert(routeSteps.begin() + insertionIndex, nodeToMove);
        utils.updateRoute(routeSteps, costMatrix);

        return true;
    }

    return false;
}