#ifndef ROUTESTEP_H
#define ROUTESTEP_H

class RouteStep {
public:

    int stationOriginId;
    int stationId;
    int cargo;
    int cost;
    int accumulatedCost;

    RouteStep() : stationId(0), cargo(0), cost(0) {}
    RouteStep(int orgin,int id, int c, int costValue = 0,int accumulatedCostvalue = 0) :stationOriginId(orgin), stationId(id), cargo(c), cost(costValue),accumulatedCost(accumulatedCostvalue) {}
};

#endif // ROUTESTEP_H