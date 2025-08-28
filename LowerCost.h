#include"InputReader.h"

class LowerCost {
private:
    int solutionValue;
    int numberOfVehicles;
    int** VehicleRoutes;
    int currentRoute;
    int* stationsNotVisited;
    int quantStationsNotVisited;
    int limitCapacityVehicle;

    void makeRoutes(node** costMatrix) { // cria uma rota para um veiculo
    int currentStation = 0;
    int VehicleLoad = 0;
    int routeIndex = 0;
    VehicleRoutes[currentRoute][routeIndex++] = currentStation; // começa na estação 0

    while (quantStationsNotVisited > 0) { // Enquanto houver estações não visitadas
        bool found = false;
        for (int i = 1; i < quantStationsNotVisited + 1; ++i) { // pega a estação com o menor custo
            int dest = costMatrix[currentStation][i].destinyStation;
            int req = costMatrix[currentStation][i].request;
            if (stationsNotVisited[dest]) { // se a estação ainda não foi visitada
                // se a requisição da estação não ultrapassa o limite nem demanda mais do que está disponível no veículo 
                if (VehicleLoad + req < limitCapacityVehicle && VehicleLoad + req > 0) { 
                    VehicleLoad += req;
                    currentStation = dest;
                    stationsNotVisited[dest] = 0;
                    VehicleRoutes[currentRoute][routeIndex++] = currentStation;
                    quantStationsNotVisited--;
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
    for (int i = 0; i < routeIndex; ++i) {
        std::cout << VehicleRoutes[currentRoute][i];
        if (i < routeIndex - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
    }    
    

public:
    LowerCost(int numberOfVehicles, int stations, int limitCapacityVehicle) {
        solutionValue = 0;
        currentRoute = 0;
        this->numberOfVehicles = numberOfVehicles;
        VehicleRoutes = new int*[numberOfVehicles];
        for (int i = 0; i < numberOfVehicles ; ++i) {
            VehicleRoutes[i] = new int[stations];
        }
        quantStationsNotVisited = stations;
        stationsNotVisited = new int[stations];
        this->limitCapacityVehicle = limitCapacityVehicle;
        stationsNotVisited[0] = 0;
        for (int i = 1; i < stations+1; ++i) {
            stationsNotVisited[i] = 1;
        }
        
    }

    void Solution(node** costMatrix ) {
       makeRoutes(costMatrix);
    }

    ~LowerCost() {
        if (VehicleRoutes != nullptr) {
            delete[] VehicleRoutes;
        }
        
        
    }
};