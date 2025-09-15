#include "../include/VND.h"

void VND::vnd(std::vector<std::vector<RouteStep>> &solution, node** &matrix, int total_cost, int vehicle_capacity){


    Swap swap(matrix);
    TwoOpt twoOpt(matrix);

    Utils utils;

    
    int count = 0;
    bool funcionou;

    do {

       funcionou = false;

        if(swap.run(solution, vehicle_capacity)) {
            funcionou = true;
            total_cost = utils.custo_total(solution);
        }

        if(twoOpt.run(solution, vehicle_capacity)) {
            funcionou = true;
            total_cost = utils.custo_total(solution);
        }

        count++;
        std::cout << "\nVND loop: " << count << std::endl;


    } while (funcionou);
   

}
