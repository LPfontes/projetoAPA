#include <iostream>
#include <istream>

class InputReader {
private:
    int stations;
    int vehicles;
    int vehicleCapacity;
    int* stationsRequests; 
    int** costMatrix; 

public:
    InputReader(std::istream& fileInput) : stations(0), vehicles(0), vehicleCapacity(0), stationsRequests(nullptr), costMatrix(nullptr) {

        fileInput >> this->stations >> this->vehicles >> this->vehicleCapacity;
        
        if (this->stations <= 0) {
            return;
        }

        this->stationsRequests = new int[this->stations];
        for (int i = 0; i < this->stations; ++i) {
            fileInput >> this->stationsRequests[i];
        }
        
        int matrizSize = this->stations + 1;
        this->costMatrix = new int*[matrizSize];
                
        for (int i = 0; i < matrizSize; ++i) {
            this->costMatrix[i] = new int[matrizSize];
            for (int j = 0; j < matrizSize; ++j) {
                fileInput >> this->costMatrix[i][j];
            }
        }
    }

    ~InputReader() {
        
        delete[] stationsRequests;

        
        if (costMatrix != nullptr) {
            int matrizSize = this->stations + 1;
            
            for (int i = 0; i < matrizSize; ++i) {
                delete[] costMatrix[i];
            }
            
            delete[] costMatrix;
        }
    }

    
    int getStations() const { return stations; }
    int getVehicles() const { return vehicles; }
    int getVehicleCapacity() const { return vehicleCapacity; }
    int* getRequests() const { return requests; }
    int** getCostMatrix() const { return costMatrix; }

    void printData() const {
        std::cout << "stations: " << stations << std::endl;
        std::cout << "vehicles: " << vehicles << std::endl;
        std::cout << "vehicleCapacity: " << vehicleCapacity << std::endl;

        if (requests != nullptr) {
            std::cout << "\nRequests array:" << std::endl;
            for (int i = 0; i < stations; ++i) {
                std::cout << requests[i] << " ";
            }
            std::cout << std::endl;
        }

        if (costMatrix != nullptr) {
            std::cout << "\nCost Matrix:" << std::endl;
            int matrizSize = stations + 1;
            for (int i = 0; i < matrizSize; ++i) {
                for (int j = 0; j < matrizSize; ++j) {
                    std::cout << costMatrix[i][j] << "\t";
                }
                std::cout << std::endl;
            }
        }
    }
};