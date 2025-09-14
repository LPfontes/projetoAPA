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
                    VehicleLoad += req;
                    if (VehicleLoad < 0) VehicleLoad = -VehicleLoad;
                    
                    stationsNotVisited[dest] = 0;
                    totalRouteCost += costMatrix[currentStation][i].cost;
                    currentRouteSteps.push_back(RouteStep{currentStation,costMatrix[currentStation][i].destinyStation, VehicleLoad, costMatrix[currentStation][i].cost,totalRouteCost});
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
        currentRouteSteps.push_back(RouteStep{currentStation,0, VehicleLoad, costMatrix[currentStation][0].cost});
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
void LowerCost::swapVerticesInRoute(int routeIndex, int posA, int posB,node** costMatrix) {
    if (routeIndex < 0 || routeIndex >= VehicleRoutes.size()) return;
    auto& route = VehicleRoutes[routeIndex];
    if (posA <= 0 || posA >= route.size() || posB <= 0 || posB >= route.size()) return;

    // Calcula o novo cargo após a troca
    int originCargo1 = (posA > 0) ? route[posA-1].cargo : 0;
    int originCargo2 = (posB > 0) ? route[posB-1].cargo : 0;

    // Verifica se a troca é válida considerando a capacidade do veículo
    int newCargoB = originCargo1 + costMatrix[route[posB].getStationOriginId()][route[posB].getStationId()].request;
    int newCargoA = originCargo2 + costMatrix[route[posA].getStationOriginId()][route[posA].getStationId()].request;

    if (newCargoB <= limitCapacityVehicle && newCargoA <= limitCapacityVehicle) {
    // Verifica se alguma das novas cargas é negativa
    if ((newCargoB < 0 && route[posA-1].getStationId() != 0) ||
        (newCargoA < 0 && route[posB-1].getStationId() != 0)) {
        return;
    }

    if (newCargoB < 0) {
    if (route[posA-1].getStationId() == 0) {
        route[posA-1].setCargo(-newCargoB);
    } 
    }
    if (newCargoA < 0) {
    if (route[posB-1].getStationId() == 0) {
        route[posB-1].setCargo(-newCargoA);
    } 
    // Realiza a troca dos stationId
    auto aux = route[posA].getStationId();
    route[posA].setStationId(route[posB].getStationId());
    route[posB].setStationId(aux);

    // Atualiza os custos acumulados após a troca
    int totalRouteCost = 0;
    for (size_t i = 0; i < route.size(); ++i) {
        if (i == 0) {
            route[i].accumulatedCost = 0;
        } else {
           
            route[i].cost = costMatrix[route[i].getStationOriginId()][route[i].getStationId()].cost;
            totalRouteCost += route[i].cost;
            route[i].accumulatedCost = totalRouteCost;
            route[i].cargo = route[i-1].cargo + costMatrix[route[i].getStationOriginId()][route[i].getStationId()].request;
        }
    }
}
}