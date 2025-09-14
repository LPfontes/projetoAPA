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

    // Calcula o totalCost da solução 
    for (size_t i = 0; i < this->solution->size(); ++i) {
        addToTotalCost((*this->solution)[i][(*this->solution)[i].size() - 1].accumulatedCost);
    }
    std::cout << "\nSolucao gulosa" << std::endl;
    printSolution();
    alg.swapVerticesInRoute(0,1,3,costMatrix);
    printSolution();
}

void Solution::printSolution() const {

    std::cout << "\nSolucao: \n\n";

    std::cout << "(Origem, Destino, Carga, Custo, Custo Acumulado)"<<std::endl;
    // Itera sobre cada rota na matriz de solução
    for (size_t i = 0; i < this->solution->size(); ++i) {
        if ((*this->solution)[i].size() == 0){
            break;
        }
        std::cout << "Rota " << i + 1 << ": ";

        // Itera sobre cada passo da rota (elemento dentro do vetor interno)
        for (size_t j = 0; j < (*this->solution)[i].size(); ++j) {
            std::cout << "(" << (*this->solution)[i][j].stationOriginId 
                        << ", " << (*this->solution)[i][j].stationId 
                        << ", " << (*this->solution)[i][j].cargo 
                        << ", " << (*this->solution)[i][j].cost 
                        << ", " << (*this->solution)[i][j].accumulatedCost << ")";

            // Adiciona o '->' apenas se não for o último passo
            if (j < (*this->solution)[i].size() - 1) {
                std::cout << " -> ";
            }
           
        }
        std::cout <<" Custo Total da Rota: " <<(*this->solution)[i][ (*this->solution)[i].size() - 1].accumulatedCost<< std::endl;
        std::cout << std::endl; // Quebra de linha após cada rota
    }
    std::cout <<" Custo Total da Solução: " <<getTotalCost()<< std::endl;
}