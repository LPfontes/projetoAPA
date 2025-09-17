#include "../include/Swap2.h"

Swap2::Swap2(node **costMatrix) : costMatrix(costMatrix) {}

bool Swap2::run(std::vector<std::vector<RouteStep>> &solution, int vehicleCapacity, int total)
{
    Utils utils;

    int bestCost = total;
    int bestI;
    int bestJ;
    int bestK;
    int bestL;
    int bestKInit;
    int bestLInit;

    for (size_t k = 0; k < solution.size(); ++k)
    {

        for (size_t l = k; l < solution.size(); ++l)
        {

            int routeSizeK = solution[k].size();
            int routeSizeL = solution[l].size();

            if ((l == k && routeSizeK < 4) || routeSizeL < 3)
            {
                continue;
            }

            for (int i = 1; i < routeSizeK - 1; ++i)
            {

                int init_k = 1;
                if (l == k)
                    init_k = i + 1;

                for (int j = init_k; j < routeSizeL - 1; ++j)
                {
                    int cost = calculateSwapCost(total, i, j, k, l, solution, costMatrix);
                    if (cost < bestCost)
                    {

                        if (k == l)
                        {

                            std::vector<RouteStep> tempRoute = solution[k];
                            std::swap(tempRoute[i], tempRoute[j]);

                            int isValid = utils.isValid(tempRoute, costMatrix, vehicleCapacity);

                            if (isValid != -1)
                            {

                                //std::cout << "\nacha que achou: " << cost << " a " << isValid << " k " << k << std::endl;
                                bestCost = cost;
                                bestI = i;
                                bestJ = j;
                                bestK = k;
                                bestL = l;
                                bestKInit = isValid;
                            }
                        }
                        else
                        {

                            // swap entre rotas diferentes
                            std::vector<RouteStep> tempK = solution[k];
                            std::vector<RouteStep> tempL = solution[l];

                            // guardar os clientes
                            RouteStep nodeI = tempK[i];
                            RouteStep nodeJ = tempL[j];

                            // fazer a troca (substituir)
                            tempK[i] = nodeJ;
                            tempL[j] = nodeI;

                            int isValidA = utils.isValid(tempK, costMatrix, vehicleCapacity);

                            if (isValidA == -1)
                                continue;

                            int isValidB = utils.isValid(tempL, costMatrix, vehicleCapacity);

                            if (isValidB != -1)
                            {

                                //std::cout << "\nacha que achou: " << cost << " a " << isValidA << " b " << isValidB << std::endl;
                                bestCost = cost;
                                bestI = i;
                                bestJ = j;
                                bestK = k;
                                bestL = l;
                                bestKInit = isValidA;
                                bestLInit = isValidB;
                            }
                        }
                    }
                }
            }
        }
    }

    if (bestCost < total)
    {
        total = bestCost;

        if (bestK == bestL)
        {

            std::swap(solution[bestK][bestI], solution[bestK][bestJ]);

            solution[bestK][0].cargo = bestKInit;
            utils.updateRoute(solution[bestK], costMatrix);
        }
        else
        {

            // swap entre rotas diferentes

            RouteStep nodeI = solution[bestK][bestI];
            RouteStep nodeJ = solution[bestL][bestJ];

            // fazer a troca (substituir)
            solution[bestK][bestI] = nodeJ;
            solution[bestL][bestJ] = nodeI;

            solution[bestK][0].cargo = bestKInit;
            solution[bestL][0].cargo = bestLInit;

            utils.updateRoute(solution[bestK], costMatrix);
            utils.updateRoute(solution[bestL], costMatrix);
        }

        return true;
    }

    return false;
}

int Swap2::calculateSwapCost(int solutionCost, int i, int j, int k, int l,
                             std::vector<std::vector<RouteStep>> &solution,
                             node **costMatrix)
{

    //std::cout << "\ncalculo: " << solutionCost << " i :" << i << " j :" << j << " k :" << k << " l :" << l << std::endl;

    // Caso 1: troca dentro da mesma rota
    if (k == l)
    {

        int prevI = solution[k][i - 1].stationId;
        int nodeI = solution[k][i].stationId;
        int nextI = solution[k][i + 1].stationId;

        int prevJ = solution[k][j - 1].stationId;
        int nodeJ = solution[k][j].stationId;
        int nextJ = solution[k][j + 1].stationId;

        if (j == i + 1)
        {
            return solutionCost - costMatrix[prevI][nodeI].cost - costMatrix[nodeI][nodeJ].cost - costMatrix[nodeJ][nextJ].cost + costMatrix[prevI][nodeJ].cost + costMatrix[nodeJ][nodeI].cost + costMatrix[nodeI][nextJ].cost;
        }
        else
        {
            return solutionCost - costMatrix[prevI][nodeI].cost - costMatrix[nodeI][nextI].cost - costMatrix[prevJ][nodeJ].cost - costMatrix[nodeJ][nextJ].cost + costMatrix[prevI][nodeJ].cost + costMatrix[nodeJ][nextI].cost + costMatrix[prevJ][nodeI].cost + costMatrix[nodeI][nextJ].cost;
        }
    }

    // Caso 2: troca entre rotas diferentes
    else
    {

        int prevI = solution[k][i - 1].stationId;
        int nodeI = solution[k][i].stationId;
        int nextI = solution[k][i + 1].stationId;

        int prevJ = solution[l][j - 1].stationId;
        int nodeJ = solution[l][j].stationId;
        int nextJ = solution[l][j + 1].stationId;

        // custo original é solutionCost = cost(r1) + cost(r2)
        // precisamos recalcular os arcos locais que mudam nas duas rotas
        int delta = 0;

        // remover arcos da rota k
        delta -= costMatrix[prevI][nodeI].cost;
        delta -= costMatrix[nodeI][nextI].cost;

        // remover arcos da rota l
        delta -= costMatrix[prevJ][nodeJ].cost;
        delta -= costMatrix[nodeJ][nextJ].cost;

        // adicionar novos arcos em k (onde entra nodeJ no lugar de nodeI)
        delta += costMatrix[prevI][nodeJ].cost;
        delta += costMatrix[nodeJ][nextI].cost;

        // adicionar novos arcos em l (onde entra nodeI no lugar de nodeJ)
        delta += costMatrix[prevJ][nodeI].cost;
        delta += costMatrix[nodeI][nextJ].cost;

        return solutionCost + delta;
    }
}
