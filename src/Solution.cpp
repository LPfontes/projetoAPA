#include "../include/Solution.h"

Solution::Solution(Instance* instance): instance(instance) {}

void Solution::bake()  {

    auto start = std::chrono::high_resolution_clock::now();

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

    //std::cout << "\nSolucao gulosa" << std::endl;
    //std::cout << "\nCuto total: " << getTotalCost() << std::endl;
    //printSolution();

    //std::cout << "\nVND" << std::endl;
    VND vnd;
    vnd.vnd(*this->solution, costMatrix, getTotalCost(), this->instance->getVehicleCapacity());

    calculateCosts();
    //std::cout << "\nCuto total: " << getTotalCost() << std::endl;

    printSolution();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    //std::cout << "Tempo de execucao: " << duration.count() << " ms\n";


}

void Solution::GAP(int bestCost) {

    // ------------------------------ guloso ----------------------------------------

    auto start = std::chrono::high_resolution_clock::now();

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

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_guloso = end - start;

    // ------------------------------------------------------------------------------

    int custo_gulosa = getTotalCost();
    //std::cout << "Heuristica construtiva:\n";
    //printGAP(bestCost, custo_gulosa, duration_guloso.count());

    // --------------------------------- VND ------------------------------------

    start = std::chrono::high_resolution_clock::now();

    VND vnd;
    vnd.vnd(*this->solution, costMatrix, getTotalCost(), this->instance->getVehicleCapacity());

    calculateCosts();

    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_vnd = end - start;

    // -----------------------------------------------------------------------

    int custo_vnd =  getTotalCost();
    //std::cout << "\nVND:\n";
    printSolution();
    //printGAP(bestCost, custo_vnd, duration_vnd.count());

  

}

void Solution::printGAP(int best, int found, double time) {

    double gap = ((static_cast<double>(found) - best) / best) * 100.0;

    std::cout << best << std::endl;
    std::cout << (*this->solution).size() << std::endl;
    std::cout << "Valor solução: " << found << std::endl;
    std::cout << "Tempo de execucao: " << time << " ms" << std::endl;
    std::cout << "Gap: " << gap << "%" << std::endl;

}

void Solution::calculateCosts() {

    setTotalCost(0);

   // Calcula o totalCost da solução 
    for (size_t i = 0; i < this->solution->size(); ++i) {
        int route_cost = (*this->solution)[i][(*this->solution)[i].size() - 1].accumulatedCost;
        addToTotalCost(route_cost);
    }
}

void Solution::printSolution() const {

    std::cout << getTotalCost() << std::endl;
    std::cout << (*this->solution).size() << std::endl;
    // Itera sobre cada rota na matriz de solução
    for (size_t i = 0; i < this->solution->size(); ++i) {
        if ((*this->solution)[i].size() == 0){
            break;
        }
        // Itera sobre cada passo da rota (elemento dentro do vetor interno)
        for (size_t j = 0; j < (*this->solution)[i].size(); ++j) {
            std::cout << (*this->solution)[i][j].stationId << " ";
        }
        std::cout << std::endl; // Quebra de linha após cada rota  
    }
}

void Solution::validateSolution() const {
    
}