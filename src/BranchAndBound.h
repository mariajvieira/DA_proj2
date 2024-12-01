#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "Graph.h"
#include "Node.h"
#include "Edge.h"


template <class T>
class BranchAndBound {
public:
    struct Result {
        std::vector<T> path;
        double cost;
    };


    explicit BranchAndBound(Graph<T>& graph) : graph(graph), bestCost(std::numeric_limits<double>::infinity()) {}

    Result solveTSP() {
    Result result;
    if (graph.getVertexSet().empty()) {
        std::cerr << "Graph is empty, cannot perform TSP." << std::endl;
        return {};
    }

    BnBNode root;
    root.path.push_back(graph.findVertex(0));
    root.visited.resize(graph.getNumVertex(), false);
    root.visited[0] = true;
    root.level = 1;
    root.lowerBound = calculateLowerBound(root);

    std::priority_queue<BnBNode> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
        BnBNode current = nodes.top();
        nodes.pop();

        if (current.level == graph.getNumVertex()) {
            if (canReturnToStart(current.path.back())) {
                BnBNode child = current;
                child.path.push_back(graph.findVertex(0));
                child.level++;

                double currentCost = calculateCost(child.path);
                if (currentCost < bestCost) {
                    bestCost = currentCost;
                    bestPath = extractPathInfo(child.path);
                }
            }
        } else {
            for (auto nextVertex : graph.getVertexSet()) {
                if (!current.visited[nextVertex->getInfo()]) {
                    BnBNode child = current;
                    child.path.push_back(nextVertex);
                    child.visited[nextVertex->getInfo()] = true;
                    child.level++;
                    child.lowerBound = calculateLowerBound(child);
                    if (child.lowerBound < bestCost) {
                        nodes.push(child);
                    }
                }
            }
        }
    }
    result.path = bestPath;
    result.cost = bestCost;
    return result;
}

bool canReturnToStart(Vertex<T>* lastVertex) {
    auto edges = lastVertex->getAdj();
    auto it = std::find_if(edges.begin(), edges.end(), [&](Edge<T>* e) { return e->getDest() == graph.findVertex(0); });
    return it != edges.end();
}


private:
    Graph<T>& graph;
    double bestCost;
    std::vector<T> bestPath;

    struct BnBNode {
        std::vector<Vertex<T>*> path;
        std::vector<bool> visited;
        double lowerBound;
        int level;

        bool operator<(const BnBNode& other) const {
            return lowerBound > other.lowerBound;
        }
    };

    double calculateLowerBound(const BnBNode& node) {
        double currentPathCost = calculateCost(node.path);
        double mstCost = calculateMSTCost(node);
        return currentPathCost + mstCost;
    }

    double calculateMSTCost(const BnBNode& node) {
        std::vector<Vertex<T>*> remainingVertices;
        for (auto vertex : graph.getVertexSet()) {
            if (!node.visited[vertex->getInfo()]) {
                remainingVertices.push_back(vertex);
            }
        }
        return mst_prim23(remainingVertices);
    }

    double calculateCost(const std::vector<Vertex<T>*>& path) {
        double cost = 0;
        for (size_t i = 0; i < path.size() - 1; ++i) {
            auto edges = path[i]->getAdj();
            auto it = std::find_if(edges.begin(), edges.end(), [&](Edge<T>* e) { return e->getDest() == path[i + 1]; });
            if (it != edges.end()) {
                cost += (*it)->getWeight();
            }
        }
        if (path.size() > 1 && path.back()->getInfo() != path.front()->getInfo()) {
            auto edges = path.back()->getAdj();
            auto it = std::find_if(edges.begin(), edges.end(), [&](Edge<T>* e) { return e->getDest() == path.front(); });
            if (it != edges.end()) {
                cost += (*it)->getWeight();
            }
        }
        return cost;
    }

    std::vector<T> extractPathInfo(const std::vector<Vertex<T>*>& path) {
        std::vector<T> infoPath;
        for (auto v : path) {
            infoPath.push_back(v->getInfo());
        }
        return infoPath;
    }

    double mst_prim23(const std::vector<Vertex<T> *> &subgraphVertices) {
        if (subgraphVertices.empty()) {
            return 0.0; //caso de erro
        }

        for (auto v : subgraphVertices) {
            v->setDist(std::numeric_limits<double>::infinity());
            v->setPath(nullptr);
            v->setVisited(false);
        }

        Vertex<T>* startVertex = subgraphVertices.front();
        startVertex->setDist(0);

        std::priority_queue<std::pair<double, Vertex<T>*>, std::vector<std::pair<double, Vertex<T>*>>, std::greater<std::pair<double, Vertex<T>*>>> pq;
        pq.push({0, startVertex});
        double totalMSTCost = 0;

        while (!pq.empty()) {
            auto [cost, v] = pq.top();
            pq.pop();
            if (v->isVisited()) {
                continue;
            }

            v->setVisited(true);
            totalMSTCost += cost;

            for (Edge<T>* e : v->getAdj()) {
                Vertex<T>* w = e->getDest();
                if (!w->isVisited() && e->getWeight() < w->getDist()) {
                    w->setDist(e->getWeight());
                    w->setPath(e);
                    pq.push({e->getWeight(), w});
                }
            }
        }

        for (auto v : subgraphVertices) {
            if (!v->isVisited()) {
                std::cerr << "Not all vertices are included in the MST. The subgraph may be disconnected." << std::endl;
                return std::numeric_limits<double>::infinity();
            }
        }

        return totalMSTCost;
    }
};

#endif // BRANCHANDBOUND_H
