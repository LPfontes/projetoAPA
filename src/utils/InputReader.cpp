#include "InputReader.h"

InputReader::InputReader(std::istream& fileInput) 
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

InputReader::~InputReader() {
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

int InputReader::getStations() const { return stations; }
int InputReader::getVehicles() const { return vehicles; }
int InputReader::getVehicleCapacity() const { return vehicleCapacity; }
int* InputReader::getRequests() const { return stationsRequests; }
node** InputReader::getCostMatrix() const { return costMatrix; }

void InputReader::orderCostMatrix() const {
    int matrizSize = stations;
    for (int i = 0; i < matrizSize; ++i) {
        std::sort(costMatrix[i] + 1, costMatrix[i] + matrizSize, [](const node& a, const node& b) {
            return a.cost < b.cost;
        });
    }
}

void InputReader::printData() const {
    std::cout << "stations: " << stations << std::endl;
    std::cout << "vehicles: " << vehicles << std::endl;
    std::cout << "vehicleCapacity: " << vehicleCapacity << std::endl;

    if (stationsRequests != nullptr) {
        std::cout << "\nRequests array:" << std::endl;
        for (int i = 0; i < stations - 1; ++i) {
            std::cout << stationsRequests[i] << " ";
        }
        std::cout << std::endl;
    }

    if (costMatrix != nullptr) {
        std::cout << "\nCost Matrix (Original):" << std::endl;
        int matrizSize = stations;
        for (int i = 0; i < matrizSize; ++i) {
            for (int j = 0; j < matrizSize; ++j) {
                std::cout << "(" << costMatrix[i][j].cost << "," << costMatrix[i][j].destinyStation << ", " << costMatrix[i][j].request << ")\t";
            }
            std::cout << std::endl;
        }
    }
    
    orderCostMatrix();
    
    if (costMatrix != nullptr) {
        std::cout << "\nCost Matrix (Ordered):" << std::endl;
        int matrizSize = stations;
        for (int i = 0; i < matrizSize; ++i) {
            for (int j = 0; j < matrizSize; ++j) {
                std::cout << "(" << costMatrix[i][j].cost << "," << costMatrix[i][j].destinyStation << ", " << costMatrix[i][j].request << ")\t";
            }
            std::cout << std::endl;
        }
    }
}