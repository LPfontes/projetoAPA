#include "InputReader.h"

class RouteStep {
public:
    int stationId;
    int cargo;
    int cost; 

    RouteStep() : stationId(0), cargo(0), cost(0) {}
    RouteStep(int id, int c, int costValue = 0) : stationId(id), cargo(c), cost(costValue) {}
};

class LowerCost {
private:
    int solutionValue;
    int numberOfVehicles;
    RouteStep** VehicleRoutes; // agora é um array de arrays de RouteStep
    int currentRoute;
    int* stationsNotVisited;
    int quantStationsNotVisited;
    int limitCapacityVehicle;
    int stations;

    void makeRoutes(node** costMatrix, int routeIndex) {
        int currentStation = 0;
        int VehicleLoad = 0;
        int stepIndex = 0;
        VehicleRoutes[currentRoute][stepIndex++] = RouteStep(currentStation, VehicleLoad); // começa na estação 0

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
                        VehicleRoutes[currentRoute][stepIndex++] = RouteStep(costMatrix[currentStation][i].destinyStation, VehicleLoad,costMatrix[currentStation][i].cost);
                        quantStationsNotVisited--;
                        currentStation = dest;
                        found = true;
                        break;
                    }
                }
            }
            if (!found) {
                break;
            }
        }

        // Imprime a rota criada
        std::cout << "Rota criada: ";
        for (int i = 0; i < stepIndex; ++i) {
            std::cout << "(" << VehicleRoutes[currentRoute][i].stationId << ", " << VehicleRoutes[currentRoute][i].cargo << ", " <<VehicleRoutes[currentRoute][i].cost << ")";
            if (i < stepIndex - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
    }

public:
    LowerCost(int numberOfVehicles, int stations, int limitCapacityVehicle) {
        solutionValue = 0;
        currentRoute = 0;
        this->stations = stations;
        this->numberOfVehicles = numberOfVehicles;
        VehicleRoutes = new RouteStep*[numberOfVehicles];
        for (int i = 0; i < numberOfVehicles; ++i) {
            VehicleRoutes[i] = new RouteStep[stations + 1];
        }
        quantStationsNotVisited = stations- 1;
        stationsNotVisited = new int[stations];
        this->limitCapacityVehicle = limitCapacityVehicle;
        stationsNotVisited[0] = 0;
        for (int i = 1; i < stations; ++i) {
            stationsNotVisited[i] = 1;
            std::cout << stationsNotVisited[i]  << std::endl;
        }
    }

    void Solution(node** costMatrix) {
        int routeIndex = 0;
        while (quantStationsNotVisited > 0) {
            makeRoutes(costMatrix, routeIndex);
            routeIndex++;
        }
    }

    ~LowerCost() {
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
};