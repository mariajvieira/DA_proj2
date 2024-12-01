#include "BranchAndBound.h"
#include "Node.h"
#include <unordered_map>

/*
template <class T>
BranchAndBound<T>::BranchAndBound(Graph<T>& graph) : graph(graph), bestCost(std::numeric_limits<double>::infinity()) {}



template <class T>
std::vector<T> BranchAndBound<T>::solveTSP() {
    BnBNode root;
    root.path.push_back(graph.getVertexSet().front());  // Start at the first vertex
    root.visited = std::vector<bool>(graph.getNumVertex(), false);
    root.visited[graph.getVertexSet().front()->getInfo()] = true;  // Assuming getInfo() returns index or unique identifier
    root.level = 1;
    root.lowerBound = calculateLowerBound(root);

    std::priority_queue<BnBNode> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
        BnBNode current = nodes.top();
        nodes.pop();

        if (current.level == graph.getNumVertex()) {
            double currentCost = calculateCost(current.path);
            if (currentCost < bestCost) {
                bestCost = currentCost;
                bestPath.clear();
                for (auto v : current.path) bestPath.push_back(v->getInfo());
            }
        } else {
            for (int i = 0; i < graph.getNumVertex(); ++i) {
                Vertex<T>* nextVertex = graph.getVertexSet()[i];
                if (!current.visited[nextVertex->getInfo()]) {
                    BnBNode child = current;
                    child.path.push_back(nextVertex);
                    child.visited[nextVertex->getInfo()] = true;
                    child.level = current.level + 1;
                    child.lowerBound = calculateLowerBound(child);

                    if (child.lowerBound < bestCost) {
                        nodes.push(child);
                    }
                }
            }
        }
    }

    return bestPath;
}

template <class T>
double BranchAndBound<T>::calculateLowerBound(const BnBNode& node) {
    // Current cost of the path followed so far.
    double currentPathCost = calculateCost(node.path);

    // Remaining vertices to be visited.
    std::vector<Vertex<T>*> remainingVertices;
    for (auto vertex : graph.getVertexSet()) {
        if (!node.visited[vertex->getInfo()]) {
            remainingVertices.push_back(vertex);
        }
    }

    // Calculate the minimum spanning tree of the remaining vertices.
    double mstCost = calculateMSTCost(remainingVertices);

    // Minimum edges connecting the current path to the MST and from MST back to the start.
    double minEntryEdge = std::numeric_limits<double>::max();
    double minExitEdge = std::numeric_limits<double>::max();

    if (!remainingVertices.empty()) {
        for (auto v : node.path) {
            for (auto e : v->getAdj()) {
                if (!node.visited[e->getDest()->getInfo()]) {
                    minEntryEdge = std::min(minEntryEdge, e->getWeight());
                }
            }
        }

        Vertex<T>* lastInPath = node.path.back();
        for (auto e : lastInPath->getAdj()) {
            if (e->getDest() == node.path.front()) {  // Assuming we need to return to the start.
                minExitEdge = std::min(minExitEdge, e->getWeight());
            }
        }
    }

    // The lower bound for this node.
    return currentPathCost + mstCost + minEntryEdge + minExitEdge;
}

template <class T>
double BranchAndBound<T>::calculateMSTCost(const std::vector<Vertex<T>*>& vertices) {
    if (vertices.empty()) return 0;

    double totalCost = 0;
    std::unordered_set<Vertex<T>*> inMST;
    std::priority_queue<std::pair<double, Vertex<T>*>, std::vector<std::pair<double, Vertex<T>*>>, std::greater<std::pair<double, Vertex<T>*>>> pq;

    // Start from the first vertex in the list.
    Vertex<T>* startVertex = vertices.front();
    pq.push({0, startVertex});

    while (!pq.empty()) {
        // Select the edge with minimum weight
        auto [cost, vertex] = pq.top();
        pq.pop();

        // If this vertex is already included in MST, continue
        if (inMST.find(vertex) != inMST.end()) continue;

        // Include this vertex in MST
        totalCost += cost;
        inMST.insert(vertex);

        // Add all adjacent vertices of the vertex
        for (Edge<T>* edge : vertex->getAdj()) {
            Vertex<T>* adjVertex = edge->getDest();
            if (inMST.find(adjVertex) == inMST.end()) {
                pq.push({edge->getWeight(), adjVertex});
            }
        }
    }

    // Check if all vertices are included in MST
    if (inMST.size() != vertices.size()) {
        // This should not happen if the subgraph is connected
        std::cerr << "Not all vertices are included in the MST. There may be disconnected components." << std::endl;
        return std::numeric_limits<double>::max();  // Return an infinitely large cost if the graph is not connected.
    }

    return totalCost;
}



template <class T>
double BranchAndBound<T>::calculateCost(const std::vector<Vertex<T>*>& path) {
    double cost = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        cost += path[i]->getAdj().front()->getWeight();  // Assuming there's a direct edge to the next vertex in the path
    }
    return cost;
}

template class BranchAndBound<int>;  // Explicit instantiation for int or any other types used
*/
