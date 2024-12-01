#ifndef EDGE_H
#define EDGE_H

class Edge_ {
private:
    int origin;
    int destination;
    double distance;

public:
    // Construtor
    Edge_(int origin, int destination, double distance)
        : origin(origin), destination(destination), distance(distance) {}

    // Getters
    int getOrigin() const { return origin; }
    int getDestination() const { return destination; }
    double getDistance() const { return distance; }

    //Para obter o reservo da edge (para undirected graphs)
    Edge_ reverse() const {
        return Edge_(destination, origin, distance);
    }
};

#endif //EDGE_H
