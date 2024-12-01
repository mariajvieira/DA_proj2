#include "backtracking.h"

using namespace std;

template <class T>
void backtracking_tsp_aux(Vertex<T>* curr_vertex, int num_nodes, int visited_count, double curr_dist, double& res, std::vector<bool>& visited) {
    // ver se todos os nós já foram visitados
    if (visited_count == num_nodes) {
        // vê a dist ao nó 0
        for (auto e : curr_vertex->getAdj()) {
            if (e->getDest()->getInfo() == 0) {
                res = std::min(res, curr_dist + e->getWeight());
                break;
            }
        }
        return;
    }

    // percorre as edges do cur vertex
    for (auto e : curr_vertex->getAdj()) {
        Vertex<T>* next_vertex = e->getDest();
        int next_node = next_vertex->getInfo();
        if (!visited[next_node]) {
            visited[next_node] = true;
            // explora o proximo recursivamnet
            backtracking_tsp_aux(next_vertex, num_nodes, visited_count + 1, curr_dist + e->getWeight(), res, visited);
            visited[next_node] = false;
        }
    }
}

template <class T>
double backtracking_tsp(Graph<T>& g) {
    double res = std::numeric_limits<double>::infinity();
    int num_nodes = g.getNumVertex();
    std::vector<bool> visited(num_nodes, false);
    // procura o starting vertex
    Vertex<T>* start_vertex = g.findVertex(0);
    if (start_vertex == nullptr) {
        std::cerr << "Starting vertex (node 0) not found in the graph." << std::endl;
        return res;
    }

    // começa do 0
    visited[0] = true;
    backtracking_tsp_aux(start_vertex, num_nodes, 1, 0, res, visited);

    return res;
}

// iniciação do template
template void backtracking_tsp_aux<int>(Vertex<int>* curr_vertex, int num_nodes, int visited_count, double curr_dist, double& res, std::vector<bool>& visited);
template double backtracking_tsp<int>(Graph<int>& g);
