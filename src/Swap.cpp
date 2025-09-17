#include "../include/Swap.h"

Swap::Swap(node **costMatrix) : costMatrix(costMatrix) {}

bool Swap::run(std::vector<std::vector<RouteStep>> &solution, int vehicle_capacity){

    bool worked = false;

    for (size_t i = 0; i < solution.size(); ++i){

        int route_cost = (solution)[i][(solution)[i].size() - 1].accumulatedCost;

        if (swap_in_route(solution[i], route_cost, vehicle_capacity)){
            worked = true;
        }
    }

    return worked;
}

int Swap::calculateSwapCost(int routeCost, int i, int j, const std::vector<RouteStep>& routeSteps, node** costMatrix) {
    int prevI = routeSteps[i - 1].stationId;  
    int nodeI = routeSteps[i].stationId;      
    int nextI = routeSteps[i + 1].stationId;  

    int prevJ = routeSteps[j - 1].stationId;  
    int nodeJ = routeSteps[j].stationId;      
    int nextJ = routeSteps[j + 1].stationId;  

    if (j == i + 1) {
        return routeCost
            // Custo removido
            - costMatrix[prevI][nodeI].cost
            - costMatrix[nodeI][nodeJ].cost
            - costMatrix[nodeJ][nextJ].cost
            // Custo adicionado
            + costMatrix[prevI][nodeJ].cost
            + costMatrix[nodeJ][nodeI].cost
            + costMatrix[nodeI][nextJ].cost;
    } else {
        return routeCost
            // Custo removido
            - costMatrix[prevI][nodeI].cost
            - costMatrix[nodeI][nextI].cost
            - costMatrix[prevJ][nodeJ].cost
            - costMatrix[nodeJ][nextJ].cost
            // Custo adicionado
            + costMatrix[prevI][nodeJ].cost
            + costMatrix[nodeJ][nextI].cost
            + costMatrix[prevJ][nodeI].cost
            + costMatrix[nodeI][nextJ].cost;
    }
}
bool Swap::swap_in_route(std::vector<RouteStep> &routeSteps, int routeCost, int vehicleCapacity) {
    int bestCost = routeCost;
    int bestI;
    int bestJ;
    int best_init;
    int routeSize = routeSteps.size();
    Utils utils;
    if (routeSize < 4){
        return false;
    }
    for (int i = 1; i < routeSize - 1; ++i){
        for (int j = i + 1; j < routeSize - 1; ++j){
            int cost = calculateSwapCost(routeCost, i, j, routeSteps, costMatrix);
            if (cost < bestCost){
                std::vector<RouteStep> tempRoute = routeSteps;

                int isValid = utils.isValid(tempRoute, costMatrix, vehicleCapacity);
                if (isValid != -1)
                {
                    routeSteps = tempRoute;
                    bestCost = cost;
                    bestI = i;
                    bestJ = j;
                    best_init = isValid;
                }
            }
        }
    }

    if (bestCost < routeCost){
        std::swap(routeSteps[bestI], routeSteps[bestJ]);
        routeSteps[0].cargo = best_init;
        utils.updateRoute(routeSteps, costMatrix);
       
        return true;
    }

    return false;
}