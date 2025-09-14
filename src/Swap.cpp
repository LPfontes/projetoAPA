#include "../include/Swap.h"

Swap::Swap(node **m) : m(m) {}

bool Swap::run(std::vector<std::vector<RouteStep>> &solution, int vehicle_capacity)
{

    bool worked = false;

    for (size_t i = 0; i < solution.size(); ++i)
    {

        int route_cost = (solution)[i][(solution)[i].size() - 1].accumulatedCost;

        if (swap_in_route(solution[i], route_cost, vehicle_capacity))
        {
            worked = true;
        }
    }

    return worked;
}

bool Swap::swap_in_route(std::vector<RouteStep> &r, int route_cost, int vehicle_capacity)
{

    int best = route_cost;
    int best_i;
    int best_j;
    int size_array = r.size();
    Utils utils;

    if (size_array < 4)
    {
        return false;
    }

    for (int i = 1; i < size_array - 1; ++i)
    {
        for (int j = i + 1; j < size_array - 1; ++j)
        {

            int cost;

            // Caso especial: os nós são adjacentes
            if (j == i + 1)
            {

                cost =

                    route_cost

                    // Custo a remover
                    - m[r[i - 1].stationId][r[i].stationId].cost 
                    - m[r[i].stationId][r[j].stationId].cost 
                    - m[r[j].stationId][r[j + 1].stationId].cost

                    // Custo a adicionar
                    + m[r[i - 1].stationId][r[j].stationId].cost 
                    + m[r[j].stationId][r[i].stationId].cost 
                    + m[r[i].stationId][r[j + 1].stationId].cost;
            }
            // Caso geral: os nós não são adjacentes
            else
            {

                cost =

                    route_cost

                    // Custo a remover
                    - m[r[i - 1].stationOriginId][r[i].stationId].cost 
                    - m[r[i].stationId][r[i + 1].stationId].cost 
                    - m[r[j].stationOriginId][r[j].stationId].cost 
                    - m[r[j].stationId][r[j + 1].stationId].cost

                    // Custo a adicionar
                    + m[r[i - 1].stationOriginId][r[j].stationId].cost 
                    + m[r[j].stationId][r[i + 1].stationId].cost 
                    + m[r[j].stationOriginId][r[i].stationId].cost 
                    + m[r[i].stationId][r[j + 1].stationId].cost;
            }

            // A nova lógica de validação:
            if (cost < best)
            {

                // Cria uma cópia temporária da rota para simular a troca
                std::vector<RouteStep> temp_route = r;

                // Valida a rota temporária
                if (utils.isValid(temp_route, m, vehicle_capacity))
                {
                    // Se a rota for válida e o custo for melhor,
                    // aplica a troca na rota original e atualiza o melhor custo.
                    r = temp_route;
                    best = cost;
                    best_i = i;
                    best_j = j;

                    // std::cout << "\nmenor e valida i: " << i << " J: " << j << std::endl;
                    // std::cout << "\nVND custo rota: " << route_cost << " novo custo " << cost << std::endl;

                } // else {
                //     std::cout << "\nmenor mas nao valido  i: " << i << " J: " << j << std::endl;
                //     std::cout << "\nVND custo rota: " << route_cost << " novo custo:" << cost << std::endl;
                // }
            }
        }
    }

    if (best < route_cost)
    {

        //std::cout << "\nbest: " << best << " routes: " << route_cost << std::endl;

        std::swap(r[best_i], r[best_j]);
        utils.updateRoute(r, m);
        return true;
    }

    return false;
}
