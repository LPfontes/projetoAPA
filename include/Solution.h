#ifndef H_SOLUTION_H
#define H_SOLUTION_H

#include <iostream>
#include <string>
#include <vector>
#include "Instance.h"
#include "LowerCost.h"
#include "Sort.h" 

class Solution {
public:

    Solution(Instance* instance);

    void bake();
    void printSolution() const;
    //const std::vector<std::vector<int>>& getSolution() const;

private:

    Instance* instance;
    std::vector<std::vector<RouteStep>>* solution; 
};

#endif // H_SOLUTION_H