#include "../include/LowerCost.h"

// Construtor
LowerCost::LowerCost(int numberOfVehicles, int stations, int limitCapacityVehicle) {

    this->stations = stations;
    this->numberOfVehicles = numberOfVehicles;
    this->limitCapacityVehicle = limitCapacityVehicle;
    
    VehicleRoutes.resize(numberOfVehicles);
    stationsNotVisited.resize(stations);

    quantStationsNotVisited = stations - 1;
    stationsNotVisited[0] = 0;
    for (int i = 1; i < stations; ++i) {
        stationsNotVisited[i] = 1;
    }
    
    currentRoute = 0;
}



// Algoritimo guloso para obter a rota inicial
void LowerCost::makeRoutes(node** costMatrix) {

    int totalRouteCost = 0;
    int currentStation = 0;
    int VehicleLoad = 0;

    std::vector<RouteStep> currentRouteSteps;
    currentRouteSteps.push_back(RouteStep{currentStation,currentStation, VehicleLoad});

    while (quantStationsNotVisited > 0) {
        bool found = false;
        for (int i = 1; i < stations; ++i) {
            int dest = costMatrix[currentStation][i].destinyStation;
            int req = costMatrix[currentStation][i].request;

            if (stationsNotVisited[dest]) {
                if ((currentStation == 0 && VehicleLoad + req < limitCapacityVehicle) ||
                    (currentStation != 0 && VehicleLoad + req < limitCapacityVehicle && VehicleLoad + req > 0)) {

                    // Se está no depósito e a requisição é negativa, atualiza a carga inicial para suprir a req
                    if (currentStation == 0 && req < 0) {
                        VehicleLoad = -req;
                        currentRouteSteps[0].cargo = VehicleLoad;
                    }

                    VehicleLoad += req;
                    if (VehicleLoad < 0) VehicleLoad = -VehicleLoad;
                    
                    stationsNotVisited[dest] = 0;
                    totalRouteCost += costMatrix[currentStation][i].cost;
                    currentRouteSteps.push_back(RouteStep{currentStation, costMatrix[currentStation][i].destinyStation, VehicleLoad, costMatrix[currentStation][i].cost, totalRouteCost});
                    quantStationsNotVisited--;
                    currentStation = dest;
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            totalRouteCost += costMatrix[currentStation][0].cost;
            currentRouteSteps.push_back(RouteStep{currentStation,0, VehicleLoad, costMatrix[currentStation][0].cost,totalRouteCost});
            break;
        }
    }
    
    if (quantStationsNotVisited == 0) {
        totalRouteCost += costMatrix[currentStation][0].cost;
        currentRouteSteps.push_back(RouteStep{currentStation,0, VehicleLoad, costMatrix[currentStation][0].cost,totalRouteCost});
    }

    VehicleRoutes[currentRoute] = currentRouteSteps;
}

std::vector<std::vector<RouteStep>>* LowerCost::Solution(node** costMatrix) {
    int routeIndex = 0;

    while (quantStationsNotVisited > 0 && routeIndex < numberOfVehicles) {
        makeRoutes(costMatrix);
        routeIndex++;
        currentRoute++;
    }

    return &VehicleRoutes;
}
