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
        for(int j = i + 3; j < routeSize -1; ++j) {
            int cost = routeCost - (routeSteps[j+1].accumulatedCost - routeSteps[i-1].accumulatedCost);
             std::cout << "(" << routeSteps[i].stationOriginId 
                        << ", " << routeSteps[i].stationId 
                        << ", " << routeSteps[i].cargo 
                        << ", " << routeSteps[i].cost 
                        << ", " << routeSteps[i].accumulatedCost << ")"
                        << "-> "<< "(" << routeSteps[j].stationOriginId 
                        << ", " << routeSteps[j].stationId 
                        << ", " << routeSteps[j].cargo 
                        << ", " << routeSteps[j].cost 
                        << ", " << routeSteps[j].accumulatedCost << ")"<< std::endl; 

            for (size_t k = j; k > i; --k) {
                std::cout << "(" << routeSteps[k].stationId<< "->" << routeSteps[k-1].stationId <<"cost : "<<costMatrix[routeSteps[k].stationId][routeSteps[k-1].stationId].cost<<std::endl;
                cost += costMatrix[routeSteps[k].stationId][routeSteps[k -1 ].stationId].cost;
            }  
            std::cout << "(" << routeSteps[i-1].stationId<< "->" << routeSteps[j].stationId <<"cost : "<<costMatrix[routeSteps[i-1].stationId][routeSteps[j].stationId].cost<<std::endl;
            std::cout << "(" << routeSteps[i].stationId<< "->" << routeSteps[j+1].stationId <<"cost : "<<costMatrix[routeSteps[i].stationId][routeSteps[j+1].stationId].cost<<std::endl;

            cost += costMatrix[routeSteps[i-1].stationId][routeSteps[j].stationId].cost;      
            cost += costMatrix[routeSteps[i].stationId][routeSteps[j+1].stationId].cost;

            if(cost < bestCost) {
                std::cout << "\neh menor: " << cost << " tm " << routeSize  << " valor da rota: " << routeCost << " i: " << i << " j " << j << std::endl;
                
            }
            
        }
    }

    return false;

}