class node {
public:
    int cost;
    int destinyStation;
    int request; 

    node() : cost(0), destinyStation(0), request(0) {}
    node(int c, int d, int r = 0) : cost(c), destinyStation(d), request(r) {}
};