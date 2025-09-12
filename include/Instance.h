#ifndef _INSTANCE_H_
#define _INSTANCE_H_

#include <iostream>
#include <istream>
#include <algorithm> 
#include "Node.h"

class Instance {
private:
    int stations;
    int vehicles;
    int vehicleCapacity;
    int* stationsRequests;
    node** costMatrix; 
public:
    
    Instance(std::istream& fileInput);
    
    ~Instance();

    int getStations() const;
    int getVehicles() const;
    int getVehicleCapacity() const;
    int* getRequests() const;
    node** getCostMatrix() const;
    
    //void orderCostMatrix() const;
    void printData() const;
};

#endif // _INSTANCE_H_