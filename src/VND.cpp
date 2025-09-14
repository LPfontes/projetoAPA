#include "../include/VND.h"

void VND::vnd(std::vector<std::vector<RouteStep>> &solution, node** &matrix, int total_cost, int vehicle_capacity){


    Swap swap(matrix);
    Utils utils;

    
    //int count = 0;
    bool funcionou;

    do {

       funcionou = false;

        if(swap.run(solution, vehicle_capacity)) {
            funcionou = true;
            total_cost = utils.custo_total(solution);
        }

        // count++;
        // std::cout << "\nVND loop: " << count << std::endl;


    } while (funcionou);
   

    // loop até que não haja mais melhorias:
    // melhoria_encontrada = falso
    
    // // Movimento 1: Swap de nós
    // if (swap_in_route(solucao) é melhor) {
    //     solucao = swap_in_route(solucao)
    //     melhoria_encontrada = true
    // }
    
    // // Movimento 2: Troca 2-opt
    // if (2_opt(solucao) é melhor) {
    //     solucao = 2_opt(solucao)
    //     melhoria_encontrada = true
    // }

    // // Movimento 3 (sua ideia): Ajuste de Carga Inicial
    // if (adjust_initial_load(solucao) é melhor) {
    //     solucao = adjust_initial_load(solucao)
    //     melhoria_encontrada = true
    // }
    
    // if (melhoria_encontrada == false) {
    //     break
    // }
}

// int VND::updateSolution(std::vector<std::vector<RouteStep>> &solution, node** &matrix) {
    
// }