#include "node.h"
#include "StationNode.h"


class LowerCost {
private:
    int solutionValue;
    int numberOfVehicles;
    int* VehicleRoutes;
    StationNode* stationsNotVisited; 
    int limitCapacityVehicle;

    void makeRoutes(int** costMatrix) {
        // ...
    }

public:
    LowerCost(int numberOfVehicles, int stations) {
        solutionValue = 0;
        this->numberOfVehicles = numberOfVehicles;
        VehicleRoutes = new int[numberOfVehicles];
        stationsNotVisited = nullptr;
        for (int i = stations - 1; i >= 0; --i) {
            StationNode* newNode = new StationNode(i);
            newNode->next = stationsNotVisited;
            stationsNotVisited = newNode;
        }
        for (int i = 0; i < numberOfVehicles; i++) {
            VehicleRoutes[i] = 0;
        }
    }

    void Solution(int& numberOfVehicles, int& stationsRequests, int**& costMatrix) {
        // ...
    }

    ~LowerCost() {
        if (VehicleRoutes != nullptr) {
            delete[] VehicleRoutes;
        }
        // Libera a lista encadeada
        while (stationsNotVisited != nullptr) {
            StationNode* temp = stationsNotVisited;
            stationsNotVisited = stationsNotVisited->next;
            delete temp;
        }
    }
};