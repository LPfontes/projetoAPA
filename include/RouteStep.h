#ifndef ROUTESTEP_H
#define ROUTESTEP_H

class RouteStep {
public:

    int stationOriginId;
    int stationId;
    int cargo;
    int cost;
    int accumulatedCost;

    RouteStep() : stationOriginId(0), stationId(0), cargo(0), cost(0), accumulatedCost(0) {}
    RouteStep(int origin, int id, int c, int costValue = 0, int accumulatedCostValue = 0)
        : stationOriginId(origin), stationId(id), cargo(c), cost(costValue), accumulatedCost(accumulatedCostValue) {}

    int getCost() const { return cost; }
    int getStationId() const { return stationId; }
    int getStationOriginId() const { return stationOriginId; }
    int getCargo() const { return cargo; }
    int getAccumulatedCost() const { return accumulatedCost; }

    // Setters
    void setCost(int value) { cost = value; }
    void setStationId(int value) { stationId = value; }
    void setStationOriginId(int value) { stationOriginId = value; }
    void setCargo(int value) { cargo = value; }
    void setAccumulatedCost(int value) { accumulatedCost = value; }
};
#endif // ROUTESTEP_H