#include "../include/Utils.h"

int Utils::isValid(std::vector<RouteStep> &routeSteps, node **&costMatrix, int vehicle_capacity)
{

    int total_cargo_needed = routeSteps[0].cargo;
    int current_cargo = total_cargo_needed;
    int increaseCargo = 0;
    bool valid;

    do {
        valid = true;
        if(total_cargo_needed < 0) {
            total_cargo_needed = total_cargo_needed * -1;
            total_cargo_needed += increaseCargo;
        }
        if(total_cargo_needed > vehicle_capacity) return -1;
        for (size_t i = 0; i < routeSteps.size(); ++i)
        {
            int cargo_at_station = 0;

            if (i == 0)
            {
                current_cargo = total_cargo_needed;
            }
            else
            {
                int station_origin_id = routeSteps[i - 1].stationId;
                int station_dest_id =routeSteps[i].stationId;
                cargo_at_station = costMatrix[station_origin_id][station_dest_id].request;
                current_cargo += cargo_at_station;
            }

            routeSteps[i].cargo = current_cargo;

            // As duas condições de validação de carga
            if (current_cargo > vehicle_capacity)
            {
                return -1;
            }if(current_cargo < 0) {
                total_cargo_needed += current_cargo;
                current_cargo = 0;
                valid = false;
            }

        }

        
    increaseCargo++;
    } while(total_cargo_needed < 0);
       
    return total_cargo_needed;

}

void Utils::updateRoute(std::vector<RouteStep> &routeSteps, node **&costMatrix)
{
    for (size_t i = 1; i < routeSteps.size(); ++i)
    {
        // Ponto de origem é a estação anterior
        int originId =routeSteps[i - 1].stationId;
        int destId =routeSteps[i].stationId;

        // 1. Atualiza o ID da estação de origem
       routeSteps[i].stationOriginId = originId;

        // 2. Atualiza o custo da viagem
        routeSteps[i].cost = costMatrix[originId][destId].cost;

        // 3. Recalcula a carga do veículo
        routeSteps[i].cargo = routeSteps[i - 1].cargo + costMatrix[originId][destId].request;

        // 4. Recalcula o custo acumulado
        routeSteps[i].accumulatedCost = routeSteps[i - 1].accumulatedCost + routeSteps[i].cost;
    }
}

int Utils::custoTotal(std::vector<std::vector<RouteStep>> &solution) {
    int total = 0;
    for (size_t i = 0; i < solution.size(); ++i) {
        int route_cost = (solution)[i][(solution)[i].size() - 1].accumulatedCost;
        total += route_cost;
        
    }
    return total;
}