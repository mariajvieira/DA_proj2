#ifndef DA_PROJ2_BACKTRACKING_H
#define DA_PROJ2_BACKTRACKING_H

#include "Graph.h"
#include <vector>
#include <limits>
#include <iostream>


template <class T>
void backtracking_tsp_aux(Vertex<T>* curr_vertex, int num_nodes, int visited_count, double curr_dist, double& res, std::vector<bool>& visited);

template <class T>
double backtracking_tsp(Graph<T>& g);

#endif // DA_PROJ2_BACKTRACKING_H
