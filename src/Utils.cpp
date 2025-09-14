#include "../include/Utils.h"

bool Utils::isValid(std::vector<RouteStep> &r, node **&m, int vehicle_capacity)
{

    int current_cargo = r[0].cargo;

    // A rota original começa com o depósito, que tem ID 0.
    // A carga inicial no depósito deve ser 0 para começar a jornada.
    // A lógica de validação deve ser baseada nas demandas de cada estação
    // e na carga acumulada.

    for (size_t i = 0; i < r.size(); ++i)
    {
        int cargo_at_station = 0;

        if (i == 0)
        {
            // A carga inicial no depósito é 0.
            current_cargo = 0;
        }
        else
        {
            int station_origin_id = r[i - 1].stationId;
            int station_dest_id = r[i].stationId;
            cargo_at_station = m[station_origin_id][station_dest_id].request;
            current_cargo += cargo_at_station;
        }

        r[i].cargo = current_cargo;

        // As duas condições de validação de carga
        if (current_cargo > vehicle_capacity || current_cargo < 0)
        {
            return false;
        }
    }
    // A rota é válida se nenhuma restrição foi violada
    return true;
}

void Utils::updateRoute(std::vector<RouteStep> &r, node **&m)
{
    for (size_t i = 1; i < r.size(); ++i)
    {
        // Ponto de origem é a estação anterior
        int originId = r[i - 1].stationId;
        int destId = r[i].stationId;

        // 1. Atualiza o ID da estação de origem
        r[i].stationOriginId = originId;

        // 2. Atualiza o custo da viagem
        r[i].cost = m[originId][destId].cost;

        // 3. Recalcula a carga do veículo
        r[i].cargo = r[i - 1].cargo + m[originId][destId].request;

        // 4. Recalcula o custo acumulado
        r[i].accumulatedCost = r[i - 1].accumulatedCost + r[i].cost;
    }
}

int Utils::custo_total(std::vector<std::vector<RouteStep>> &solution) {

    int total = 0;

    for (size_t i = 0; i < solution.size(); ++i) {

        int route_cost = (solution)[i][(solution)[i].size() - 1].accumulatedCost;
        total += route_cost;
        
    }
    return total;
}