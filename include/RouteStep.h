#ifndef ROUTESTEP_H
#define ROUTESTEP_H

class RouteStep {
public:
    int stationId;
    int cargo;
    int cost;

    RouteStep() : stationId(0), cargo(0), cost(0) {}
    RouteStep(int id, int c, int costValue = 0) : stationId(id), cargo(c), cost(costValue) {}
};

#endif // ROUTESTEP_H