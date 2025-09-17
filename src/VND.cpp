#include "../include/VND.h"

void VND::vnd(std::vector<std::vector<RouteStep>> &solution, node** &matrix, int total_cost, int vehicle_capacity){

    Utils utils;
    TwoOpt twoOpt(matrix);
    ReInsertion reInsertion(matrix);
    Swap2 swap2(matrix);

    int count = 0;
    bool funcionou;

    do {

       funcionou = false;

        if(twoOpt.run(solution, vehicle_capacity)) {
            funcionou = true;
            total_cost = utils.custo_total(solution);
            //std::cout << "\nTwoOPT funcionou: " << total_cost << std::endl;
        }

        if(swap2.run(solution, vehicle_capacity, total_cost)) {
            funcionou = true;
            total_cost = utils.custo_total(solution);
            // std::cout << "\nSWAP2 funcionou: " << total_cost << std::endl;
        }

        if(reInsertion.run(solution, vehicle_capacity)) {
            funcionou = true;
            total_cost = utils.custo_total(solution);
            // std::cout << "\nREINSERTION funcionou: " << total_cost << std::endl;
        }

        count++;
        //std::cout << "\nVND loop: " << count << std::endl;


    } while (funcionou);
   

}
