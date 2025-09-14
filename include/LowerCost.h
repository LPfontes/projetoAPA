#ifndef LOWERCOST_H
#define LOWERCOST_H

#include "Instance.h"
#include "RouteStep.h"  
#include "Node.h"
#include <vector>
#include <iostream>

class LowerCost {
private:
    
    std::vector<std::vector<RouteStep>> VehicleRoutes;
    int stations;
    int numberOfVehicles;
    int quantStationsNotVisited;
    std::vector<int> stationsNotVisited;
    int limitCapacityVehicle;
    int currentRoute;
    int totalRouteCost = 0;
    int totalCost = 0;
    void makeRoutes(node** costMatrix);

public:

    LowerCost(int numberOfVehicles, int stations, int limitCapacityVehicle);
    std::vector<std::vector<RouteStep>>* Solution(node** costMatrix);
    void swapVerticesInRoute(int routeIndex, int posA, int posB,node** costMatrix);
};

#endif // LOWERCOST_H