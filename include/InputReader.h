#ifndef _INPUTREADER_H_
#define _INPUTREADER_H_

#include <iostream>
#include <istream>
#include <algorithm> 
#include "Node.h"

class InputReader {
private:
    int stations;
    int vehicles;
    int vehicleCapacity;
    int* stationsRequests;
    node** costMatrix; 
public:
    
    InputReader(std::istream& fileInput);
    
    ~InputReader();

    int getStations() const;
    int getVehicles() const;
    int getVehicleCapacity() const;
    int* getRequests() const;
    node** getCostMatrix() const;
    
    void orderCostMatrix() const;
    void printData() const;
};

#endif // _INPUTREADER_H_