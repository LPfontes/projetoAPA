#include "../include/Solution.h"

Solution::Solution(Instance* inst): instance(inst) {}

void Solution::bake()  {

    Sorter sorter;
    node** costMatrix = instance->getCostMatrix();
    int matrixSize = instance->getStations();
    setTotalCost(0);
   
    LowerCost alg(instance->getVehicles(), instance->getStations(), instance->getVehicleCapacity());

    //passa um copia da matriz ordenada
    //copia pq vamos precisa dela normal para o VND

    this->solution = alg.Solution(sorter.sortByCopy(costMatrix, matrixSize));
    // Remove rotas vazias do vetor solution
    for (auto it = this->solution->begin(); it != this->solution->end(); ) {
        if (it->size() == 0) {
            it = this->solution->erase(it);
        } else {
            ++it;
        }
    }

    calculateCosts();

    std::cout << "\nSolucao gulosa" << std::endl;
    std::cout << "\nCuto total: " << getTotalCost() << std::endl;
    printSolution();


    std::cout << "\nVND" << std::endl;
    VND vnd;
    vnd.vnd(*this->solution, costMatrix, getTotalCost(), this->instance->getVehicleCapacity());

    calculateCosts();
    std::cout << "\nCuto total: " << getTotalCost() << std::endl;

    printSolution();


}

void Solution::calculateCosts() {

    setTotalCost(0);

   // Calcula o totalCost da solução 
    for (size_t i = 0; i < this->solution->size(); ++i) {
        int route_cost = (*this->solution)[i][(*this->solution)[i].size() - 1].accumulatedCost;
        addToTotalCost(route_cost);
    }
