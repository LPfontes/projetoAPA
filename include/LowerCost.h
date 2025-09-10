#ifndef LOWERCOST_H
#define LOWERCOST_H

#include "InputReader.h"
#include "RouteStep.h"  
#include <iostream>

class LowerCost {
private:
    int solutionValue;
    int numberOfVehicles;
    RouteStep** VehicleRoutes;
    int currentRoute;
    int* stationsNotVisited;
    int quantStationsNotVisited;
    int limitCapacityVehicle;
    int stations;

    void makeRoutes(node** costMatrix, int routeIndex);

public:
    
    LowerCost(int numberOfVehicles, int stations, int limitCapacityVehicle);

    void Solution(node** costMatrix);

    ~LowerCost();
};

#endif // LOWERCOST_H