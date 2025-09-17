#include "../include/TwoOpt.h"
#include "../include/Utils.h"

TwoOpt::TwoOpt(node **costMatrix) : costMatrix(costMatrix) {}

bool TwoOpt::run(std::vector<std::vector<RouteStep>> &solution, int vehicle_capacity) {

    bool worked = false;

    for (size_t i = 0; i < solution.size(); ++i)
    {
        int route_cost = solution[i].back().accumulatedCost;

        if (twoopt_in_route(solution[i], route_cost, vehicle_capacity))
        {
            worked = true;
        }
    }

    return worked;

}

bool TwoOpt::twoopt_in_route(std::vector<RouteStep> &routeSteps, int routeCost, int vehicleCapacity) {

    int bestCost = routeCost;
    int bestI = -1;
    int bestJ = -1;
    int routeSize = routeSteps.size();
    Utils utils;

    if(routeSize < 6) {
        return false;
    }

    // Busca o melhor movimento 2-opt
    for(int i = 1; i < routeSize -1; ++i) {
        for(int j = i + 3; j < routeSize -1; ++j) {
            int cost = routeCost - (routeSteps[j+1].accumulatedCost - routeSteps[i-1].accumulatedCost);

            for (size_t k = j; k > i; --k) {
                cost += costMatrix[routeSteps[k].stationId][routeSteps[k -1].stationId].cost;
            }  
            
            cost += costMatrix[routeSteps[i-1].stationId][routeSteps[j].stationId].cost;      
            cost += costMatrix[routeSteps[i].stationId][routeSteps[j+1].stationId].cost;

            if(cost < bestCost) {
                bestI = i;
                bestJ = j;
                bestCost = cost;
            }
        }
    }

    // Se encontrou uma melhoria, aplica a troca
    if (bestI != -1 && bestJ != -1) {
        std::vector<RouteStep> tempRoute = routeSteps;

        // Inverte o segmento entre bestI e bestJ
        std::reverse(tempRoute.begin() + bestI, tempRoute.begin() + bestJ + 1);

        // Atualiza custos e cargas do tempRoute
        int totalRouteCost = 0;
        for (size_t idx = 1; idx < tempRoute.size(); ++idx) {
            tempRoute[idx].cost = costMatrix[tempRoute[idx-1].stationId][tempRoute[idx].stationId].cost;
            totalRouteCost += tempRoute[idx].cost;
            tempRoute[idx].accumulatedCost = totalRouteCost;
            tempRoute[idx].cargo = tempRoute[idx-1].cargo + costMatrix[tempRoute[idx-1].stationId][tempRoute[idx].stationId].request;
        }

        if (utils.isValid(tempRoute, costMatrix, vehicleCapacity) != -1) {
            routeSteps = tempRoute;
            return true;
        }
    }

    return false;
}