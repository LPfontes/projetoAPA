#include "../include/Instance.h"

Instance::Instance(std::istream& fileInput) 
    : stations(0), vehicles(0), vehicleCapacity(0), stationsRequests(nullptr), costMatrix(nullptr) {

    fileInput >> this->stations >> this->vehicles >> this->vehicleCapacity;
    this->stations++;
    if (this->stations <= 0) {
        return;
    }

    this->stationsRequests = new int[this->stations - 1];
    for (int i = 0; i < this->stations - 1; ++i) {
        fileInput >> this->stationsRequests[i];
    }

    int matrizSize = this->stations;
    this->costMatrix = new node*[matrizSize];

    for (int i = 0; i < matrizSize; ++i) {
        this->costMatrix[i] = new node[matrizSize];
        for (int j = 0; j < matrizSize; ++j) {
            int costValue;
            fileInput >> costValue;
            this->costMatrix[i][j] = node(costValue, j, (j == 0) ? 0 : stationsRequests[j - 1]);
        }
    }
}

Instance::~Instance() {
    delete[] stationsRequests;
    if (costMatrix != nullptr) {
        // Correção na matrizSize, deve ser 'stations', não 'stations + 1'
        int matrizSize = this->stations;
        for (int i = 0; i < matrizSize; ++i) {
            delete[] costMatrix[i];
        }
        delete[] costMatrix;
    }
}

int Instance::getStations() const { return stations; }
int Instance::getVehicles() const { return vehicles; }
int Instance::getVehicleCapacity() const { return vehicleCapacity; }
int* Instance::getRequests() const { return stationsRequests; }
node** Instance::getCostMatrix() const { return costMatrix; }


void Instance::printData() const {

    std::cout << "\nDados da instancia:\n" << std::endl;

    std::cout << "stations: " << stations << std::endl;
    std::cout << "vehicles: " << vehicles << std::endl;
    std::cout << "vehicleCapacity: " << vehicleCapacity << std::endl;

    if (stationsRequests != nullptr) {
        std::cout << "\nRequests array:\n" << std::endl;
        for (int i = 0; i < stations - 1; ++i) {
            std::cout << stationsRequests[i] << " ";
        }
        std::cout << std::endl;
    }

    if (costMatrix != nullptr) {
        std::cout << "\nCost Matrix:\n" << std::endl;
        int matrizSize = stations;
        for (int i = 0; i < matrizSize; ++i) {
            for (int j = 0; j < matrizSize; ++j) {
                std::cout << "(" << costMatrix[i][j].cost << "," << costMatrix[i][j].destinyStation << ", " << costMatrix[i][j].request << ")\t";
            }
            std::cout << std::endl;
        }
    }

}