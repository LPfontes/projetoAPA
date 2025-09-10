#include "LowerCost.h"
#include <iostream>

// Construtor
LowerCost::LowerCost(int numberOfVehicles, int stations, int limitCapacityVehicle) {
    solutionValue = 0;
    currentRoute = 0;
    this->stations = stations;
    this->numberOfVehicles = numberOfVehicles;
    VehicleRoutes = new RouteStep*[numberOfVehicles];
    for (int i = 0; i < numberOfVehicles; ++i) {
        VehicleRoutes[i] = new RouteStep[stations + 1];
    }
    quantStationsNotVisited = stations - 1;
    stationsNotVisited = new int[stations];
    this->limitCapacityVehicle = limitCapacityVehicle;
    stationsNotVisited[0] = 0;
    for (int i = 1; i < stations; ++i) {
        stationsNotVisited[i] = 1;
    }
}

// Destrutor
LowerCost::~LowerCost() {
    if (VehicleRoutes != nullptr) {
        for (int i = 0; i < numberOfVehicles; ++i) {
            delete[] VehicleRoutes[i];
        }
        delete[] VehicleRoutes;
    }
    if (stationsNotVisited != nullptr) {
        delete[] stationsNotVisited;
    }
}

// Implementação do método privado
void LowerCost::makeRoutes(node** costMatrix, int routeIndex) {
    int currentStation = 0;
    int VehicleLoad = 0;
    int stepIndex = 0;
    VehicleRoutes[currentRoute][stepIndex++] = RouteStep(currentStation, VehicleLoad);

    while (quantStationsNotVisited > 0) {
        bool found = false;
        for (int i = 1; i < stations; ++i) {
            int dest = costMatrix[currentStation][i].destinyStation;
            int req = costMatrix[currentStation][i].request;
            if (stationsNotVisited[dest]) {
                if ((currentStation == 0 && VehicleLoad + req < limitCapacityVehicle) ||
                    (currentStation != 0 && VehicleLoad + req < limitCapacityVehicle && VehicleLoad + req > 0)) {
                    VehicleLoad += req;
                    if (VehicleLoad < 0) VehicleLoad = -VehicleLoad;
                    
                    stationsNotVisited[dest] = 0;
                    VehicleRoutes[currentRoute][stepIndex++] = RouteStep(costMatrix[currentStation][i].destinyStation, VehicleLoad, costMatrix[currentStation][i].cost);
                    quantStationsNotVisited--;
                    currentStation = dest;
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            VehicleRoutes[currentRoute][stepIndex++] = RouteStep(0, VehicleLoad, costMatrix[currentStation][0].cost);
            break;
        }
    }
    if (quantStationsNotVisited == 0) {
        VehicleRoutes[currentRoute][stepIndex++] = RouteStep(0, VehicleLoad, costMatrix[currentStation][0].cost);
    }

    std::cout << "Rota criada: ";
    for (int i = 0; i < stepIndex; ++i) {
        std::cout << "(" << VehicleRoutes[currentRoute][i].stationId << ", " << VehicleRoutes[currentRoute][i].cargo << ", " << VehicleRoutes[currentRoute][i].cost << ")";
        if (i < stepIndex - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
}

// Implementação do método público
void LowerCost::Solution(node** costMatrix) {
    int routeIndex = 0;
    while (quantStationsNotVisited > 0) {
        makeRoutes(costMatrix, routeIndex);
        routeIndex++;
        currentRoute++; // Incrementa a rota atual para o próximo veículo
    }
}