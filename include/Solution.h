#ifndef H_SOLUTION_H
#define H_SOLUTION_H 

#include <iostream>
#include <string>
#include <vector>
#include "Instance.h"
#include "LowerCost.h"
#include "Sort.h" 
#include "VND.h"

class Solution {
public:

    Solution(Instance* instance);

    void bake();
    void printSolution() const;
    //const std::vector<std::vector<int>>& getSolution() const;

    void calculateCosts();
    int getTotalCost() const { return totalCost; }
    void setTotalCost(int value) { totalCost = value; }
    void addToTotalCost(int value) { totalCost += value; }
    void validateSolution() const;

private:

    Instance* instance;
    std::vector<std::vector<RouteStep>>* solution; 
    int totalCost;
};

#endif // H_SOLUTION_H