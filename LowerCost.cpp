class LowerCost{
    private:
    int solutionValue;
    int numberOfVehicles;
    int* VehicleRoutes;
    int* stationsNotVisited;
    int limitCapacityVehicle;
    void makeRoutes(int** costMatrix){
        for(int i = 0; i < numberOfVehicles; i++){
            int currentStation = 0;
            int nextStation = -1;
            int minCost = INT_MAX;
            int vehicleCapacity = 0;
            while(stationsNotVisited > 0){
                for(int j = 1; j < stations; j++){
                    if(costMatrix[currentStation][j] < minCost && stationsRequests[j] + vehicleCapacity > limitCapacityVehicle){
                        minCost = costMatrix[currentStation][j];
                        nextStation = j;
                    }
                }
                if(nextStation != -1){
                    VehicleRoutes[i] += minCost;
                    solutionValue += minCost;
                    currentStation = nextStation;
                    stationsRequests[nextStation]--;
                    if(stationsRequests[nextStation] == 0){
                        stationsNotVisited--;
                    }
                    minCost = INT_MAX;
                    nextStation = -1;
                } else {
                    break;
                }
            }
            VehicleRoutes[i] += costMatrix[currentStation][0];
            solutionValue += costMatrix[currentStation][0];
        }
    }
    public: 
    LowerCost(int numberOfVehicles, int& stations){
    solutionValue = 0;
    this->numberOfVehicles = numberOfVehicles;
    VehicleRoutes = new int[numberOfVehicles];
    stationsNotVisited = stations;
    for(int i = 0; i < numberOfVehicles; i++){
        VehicleRoutes[i] = 0;

    }
    void Solution(int& numberOfVehicles, int& stationsRequests, int**& costMatrix){
        
    }
    ~LowerCost(){
        if(VehicleRoutes != nullptr){
            delete[] VehicleRoutes;
        }
    }

    }
}
