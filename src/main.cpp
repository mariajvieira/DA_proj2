#include <iostream>
#include "Utilities.h"
#include "BranchAndBound.h"
#include "triangular_approx.h"
#include "Graph.h"
#include "Menu.h"

int main() {

    /*
    std::string edgeFile = "../Data/Toy-Graphs/stadiums.csv";
    //std::string nodeFile = "../Data/Real-world Graphs/graph1/nodes.csv";
    auto edgesMap = Utilities::readEdges(edgeFile);
    //auto nodesMap = Utilities::readNodes(nodeFile);
    auto graph = Utilities::createGraphFromEdgeMap<int>(edgesMap);

    // Test Floyd-Warshall Algorithm
    graph->floydWarshall();
    std::cout << "Floyd-Warshall Distance Matrix:" << std::endl;
    for (int i = 0; i < graph->getNumVertex(); ++i) {
        for (int j = 0; j < graph->getNumVertex(); ++j) {
            if (graph->distMatrix[i][j] == std::numeric_limits<double>::infinity())
                std::cout << "INF ";
            else
                std::cout << graph->distMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Test Prim's MST
    auto mstEdges = graph->primMST();
    std::cout << "MST Edges:" << std::endl;
    double totalWeightMST = 0;
    for (auto e : mstEdges) {
        std::cout << e->getOrig()->getInfo() << " - " << e->getDest()->getInfo()
                  << ": " << e->getWeight() << std::endl;
        totalWeightMST += e->getWeight();
    }
    std::cout << "Total weight of MST: " << totalWeightMST << std::endl;

    // Test Eulerian Circuit (assuming graph is modified to be Eulerian)
    auto circuit = graph->findEulerianCircuit(mstEdges);
    std::cout << "Eulerian Circuit: ";
    for (int v : circuit) {
        std::cout << v << " -> ";
    }
    std::cout << "back to start" << std::endl;

    // Test converting Eulerian to Hamiltonian Circuit
    auto hamiltonian = graph->convertEulerianToHamiltonian(circuit);
    std::cout << "Hamiltonian Circuit: ";
    for (int v : hamiltonian) {
        std::cout << v << " -> ";
    }
    std::cout << "back to start" << std::endl;

    //tspApproximation(*graph);
    BranchAndBound<int> bnb(*graph);

    // Solve the TSP
    auto result = bnb.solveTSP();

    // Output the results
    std::cout << "Optimal TSP Route Cost: " << result.cost << std::endl;
    std::cout << "Optimal TSP Route: ";
    for (auto v : result.path) {
        std::cout << v << " -> ";
    }
    std::cout << result.path.front() << std::endl;  // To complete the cycle in the output

    // Clean up
    delete graph;
     */

    Menu menu;
    menu.displayMainMenu();
    return 0;
}
