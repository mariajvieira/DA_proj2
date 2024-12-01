#ifndef DA_PROJ2_TRIANGULAR_APPROX_H
#define DA_PROJ2_TRIANGULAR_APPROX_H

#include "Graph.h"
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include "MutablePriorityQueue.h"
#define EARTH_RADIUS_KM 6371.0

using namespace std;


static double haversine(double lat1, double lon1, double lat2, double lon2) {
    double rad_lat1 = lat1 * M_PI / 180;
    double rad_lon1 = lon1 * M_PI / 180;
    double rad_lat2 = lat2 * M_PI / 180;
    double rad_lon2 = lon2 * M_PI / 180;

    double delta_lat = rad_lat2 - rad_lat1;
    double delta_lon = rad_lon2 - rad_lon1;

    double a = sin(delta_lat / 2) * sin(delta_lat / 2) +
               cos(rad_lat1) * cos(rad_lat2) *
               sin(delta_lon / 2) * sin(delta_lon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return EARTH_RADIUS_KM * c;
}


template <class T>
vector<Vertex<T> *> mst_prim(Graph<T> *g);

template <class T>
void tspApproximation(Graph<T>& g);

#endif //DA_PROJ2_TRIANGULAR_APPROX_H
