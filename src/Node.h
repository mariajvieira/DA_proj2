#ifndef NODE_H
#define NODE_H

#include <cmath>

class Node {
private:
    int id;
    double longitude;
    double latitude;

public:
    // Default constructor
    Node() : id(0), longitude(0.0), latitude(0.0) {}

    // Construtor
    Node(int id, double longitude, double latitude) : id(id), longitude(longitude), latitude(latitude) {}

    // Getters
    int getId() const { return id; }
    double getLongitude() const { return longitude; }
    double getLatitude() const { return latitude; }

    // Cálculo das distâncias usando a Fórmula Haversine
    double distanceTo(const Node& other) const {
        const double earthRadiusKm = 6371.0;
        double latRad1 = latitude * M_PI / 180;
        double latRad2 = other.latitude * M_PI / 180;
        double lonRad1 = longitude * M_PI / 180;
        double lonRad2 = other.longitude * M_PI / 180;

        double dLat = latRad2 - latRad1;
        double dLon = lonRad2 - lonRad1;

        double a = sin(dLat / 2) * sin(dLat / 2) +
                   cos(latRad1) * cos(latRad2) *
                   sin(dLon / 2) * sin(dLon / 2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        return earthRadiusKm * c;
    }
};

#endif // NODE_H
