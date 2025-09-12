#include "Solution.h"

Solution::Solution(Instance* instance): instance(instance) {}

void Solution::bake()  {

    Sorter sorter;
    node** costMatrix = instance->getCostMatrix();
    int matrixSize = instance->getStations();
   
    LowerCost alg(instance->getVehicles(), instance->getStations(), instance->getVehicleCapacity());

    //passa um copia da matriz ordenada
    //copia pq vamos precisa dela normal para o VND
    this->solution = alg.Solution(sorter.sortByCopy(costMatrix, matrixSize));

    std::cout << "\nSolucao gulosa" << std::endl;
    printSolution();

}

void Solution::printSolution() const {

    std::cout << "\nSolucao: \n\n";


    // Itera sobre cada rota na matriz de solução
    for (size_t i = 0; i < this->solution->size(); ++i) {
        std::cout << "Rota " << i + 1 << ": ";

        // Itera sobre cada passo da rota (elemento dentro do vetor interno)
        for (size_t j = 0; j < (*this->solution)[i].size(); ++j) {
            std::cout << "(" << (*this->solution)[i][j].stationId 
                      << ", " << (*this->solution)[i][j].cargo 
                      << ", " << (*this->solution)[i][j].cost << ")";

            // Adiciona o '->' apenas se não for o último passo
            if (j < (*this->solution)[i].size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl; // Quebra de linha após cada rota
    }
}