#include "triangular_approx.h"

// Explicit instantiation for mst_prim with int as the template argument
template vector<Vertex<int> *> mst_prim<int>(Graph<int> *g);

// Explicit instantiation for tspApproximation with int as the template argument
template void tspApproximation<int>(Graph<int>& g);


#include "Graph.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include "MutablePriorityQueue.h"

template <class T>
vector<Vertex<T> *> mst_prim(Graph<T> *g) {
    if (g->getVertexSet().empty()) {
        return g->getVertexSet();
    }
    for(auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }
    Vertex<T>* s = g->getVertexSet().front();
    s->setDist(0);

    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);

    while(!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);

        for(auto &e : v->getAdj()) {
            Vertex<T>* w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getDist();
                if(e->getWeight() < oldDist) {
                    w->setDist(e->getWeight());
                    w->setPath(e);

                    if (oldDist == INF) {
                        q.insert(w);
                    } else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }
    return g->getVertexSet();
}

template <class T>
void tspApproximation(Graph<T>& g) {
    auto mstVertices = mst_prim(&g);

    std::unordered_map<T, bool> visited;

    std::vector<Vertex<T> *> tour;

    Vertex<T>* startVertex = nullptr;
    for (auto v : g.getVertexSet()) {
        if (v->getInfo() == 0) {
            startVertex = v;
            break;
        }
    }
    if (!startVertex) {
        std::cerr << "Start vertex with zero-identifier not found." << std::endl;
        return;
    }

    std::function<void(Vertex<T>*)> dfs = [&](Vertex<T>* v) {
        visited[v->getInfo()] = true;
        tour.push_back(v);

        std::vector<Edge<T>*> edges = v->getAdj();
        std::sort(edges.begin(), edges.end(), [](Edge<T>* a, Edge<T>* b) {
            return a->getWeight() < b->getWeight();
        });

        for (auto edge : edges) {
            if (!visited[edge->getDest()->getInfo()]) {
                dfs(edge->getDest());
            }
        }
    };

    dfs(startVertex);
    tour.push_back(startVertex);

    double final_dist = 0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        Vertex<T>* current = tour[i];
        Vertex<T>* next = tour[i + 1];

        for (auto edge : current->getAdj()) {
            if (edge->getDest() == next) {
                final_dist += edge->getWeight();
                break;
            }
        }
    }

    std::cout << "Hamiltonian path: ";
    for (const auto& node : tour) {
        std::cout << node->getInfo() << " ";
    }
    std::cout << "\nSum of all the costs in the tour: " << final_dist << std::endl;
}
