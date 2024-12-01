#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include "Utilities.h"
#include "Edge.h"
#include "backtracking.h"

class Menu {
    Utilities util;

public:
    void displayMainMenu() {
        int choice = 0;
        do {
            std::cout << "\n**********************  Travel Salesman Problem  **********************\n";

            std::cout << " 1. Backtracking Algorithm (4.1) \n";
            std::cout << " 2. Triangular Approximation Heuristic (4.2) \n";
            std::cout << " 3. Branch and Bound (4.3) \n";
            std::cout << " 4. TSP in the Real World (4.4) \n";
            std::cout << " 5. Consult graph data \n";
            std::cout << " 6. Exit\n";
            std::cout << " Choose one of the above:\n";
            std::cin >> choice;

            if (!processChoices(choice)) {
                break;
            }
        } while (true);
    }

    bool processChoices(int choice) {
        switch (choice) {
            case 1:
                displayT1();
                return true;
            case 2:
                displayT2();
                return true;
            case 3:
                displayT3();
                return true;
            case 4:
                displayT4();
                return true;
            case 5:
                displayConsult();
                return true;
            case 6:
                return false;
            default:
                std::cout << "Invalid option. Try again\n";
                return true;
        }
    }

    void displayT1() {
        std::cout << " The backtracking algorithm is available for the following graphs: \n";
        std::cout << " 1. Shipping \n";
        std::cout << " 2. Stadiums \n";
        std::cout << " 3. Tourism \n";
        std::cout << " 4. Return to main menu\n";
        std::cout << " Choose one of the above:\n";
        int choice;
        std::cin >> choice;

        std::string File;
        std::unordered_map<int, std::vector<Edge_>> edgesMap;
        Graph<int>* graph;
        double res;

        auto start = std::chrono::steady_clock::now(); // Start timing

        switch (choice) {
            case 1:
                File = "../Data/Toy-Graphs/shipping.csv";
                break;
            case 2:
                File = "../Data/Toy-Graphs/stadiums.csv";
                break;
            case 3:
                File = "../Data/Toy-Graphs/tourism.csv";
                break;
            case 4:
                displayMainMenu();
                return;
            default:
                std::cout << "Invalid option. Returning to main menu.\n";
                return;
        }

        edgesMap = Utilities::readEdges(File);
        graph = Utilities::createGraphFromEdgeMap<int>(edgesMap);
        res = backtracking_tsp(*graph);

        auto end = std::chrono::steady_clock::now(); // End timing
        std::chrono::duration<double> elapsed_seconds = end - start; // Calculate elapsed time

        std::cout << "Total cost of the path: " << res << '\n';
        std::cout << "Execution time: " << elapsed_seconds.count() << "s\n";
    }

    void displayT2() {}
    void displayT3() {}
    void displayT4() {}

    void displayConsult() {
        std::cout << " 1. Consult Toy Graphs (small graphs) data\n";
        std::cout << " 2. Consult Real-world Graphs data\n";
        std::cout << " 3. Consult Medium-Size Graphs data\n";
        std::cout << " 4. Return to main menu\n";
        std::cout << "\nEnter your choice: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                displayToyGraphsData();
                break;
            case 2:
                displayRealWorldGraphsData();
                break;
            case 3:
                //displayExtraFullyConnectedGraphsData(); NAO SEI SE FAZ SENTIDO DAR DISPLAY DESTES
                break;
            case 4:
                displayMainMenu();
                break;
            default:
                std::cout << "Invalid option. Returning to main menu.\n";
        }
    }

    void displayToyGraphsData() {
        std::vector<std::string> filenames = {
            "../Data/Toy-Graphs/shipping.csv",
            "../Data/Toy-Graphs/stadiums.csv",
            "../Data/Toy-Graphs/tourism.csv"
        };

        for (const auto& filename : filenames) {
            std::cout << "\nDisplaying data for: " << filename << std::endl;
            auto edgesMap = util.readEdges(filename);

            int totalEdges = 0;
            for (const auto& pair : edgesMap) {
                totalEdges += pair.second.size();
            }

            std::cout << "Number of unique origin vertices: " << edgesMap.size() << std::endl;
            std::cout << "Total number of edges: " << totalEdges << std::endl;

            // Print all edges
            std::cout << "Listing all edges:\n";
            for (const auto& pair : edgesMap) {
                int origin = pair.first;
                const auto& edges = pair.second;
                for (const auto& edge : edges) {
                    std::cout << "Origin: " << origin
                              << ", Destination: " << edge.getDestination()
                              << ", Distance: " << edge.getDistance() << " km" << std::endl;
                }
            }
        }
    }

    void displayRealWorldGraphsData() {
        std::vector<std::string> edgefilenames = {
                "../Data/Real-World Graphs/graph1/edges.csv",
                "../Data/Real-World Graphs/graph2/edges.csv",
                "../Data/Real-World Graphs/graph3/edges.csv"
        };

        std::vector<std::string> nodefilenames = {
                "../Data/Real-World Graphs/graph1/nodes.csv",
                "../Data/Real-World Graphs/graph2/nodes.csv",
                "../Data/Real-World Graphs/graph3/nodes.csv"
        };

        for (int i=0; i<3; i++) {
            std::cout << "\nDisplaying data for: " << edgefilenames[i] << ", " << nodefilenames[i] << std::endl;
            auto edgesMap = util.readEdges(edgefilenames[i]);
            auto nodeMap = util.readNodes(nodefilenames[i]);

            int totalEdges = 0;
            for (const auto& pair : edgesMap) {
                totalEdges += pair.second.size();
            }
            int totalNodes = nodeMap.size();
            std::cout << "Total number of edges: " << totalEdges << std::endl;
            std::cout << "Total number of nodes: " << totalNodes << std::endl;

        }
    }

    void displayExtraFullyConnectedGraphsData() {
        std::vector<std::string> edgefilenames = {
                "../Data/Extra_Fully_Connected_Graphs/edges_25.csv",
                "../Data/Extra_Fully_Connected_Graphs/edges_50.csv"
                "../Data/Extra_Fully_Connected_Graphs/edges_75.csv"
                "../Data/Extra_Fully_Connected_Graphs/edges_100.csv"
                "../Data/Extra_Fully_Connected_Graphs/edges_200.csv"
                "../Data/Extra_Fully_Connected_Graphs/edges_300.csv"
                "../Data/Extra_Fully_Connected_Graphs/edges_400.csv"
                "../Data/Extra_Fully_Connected_Graphs/edges_500.csv"
                "../Data/Extra_Fully_Connected_Graphs/edges_600.csv"
                "../Data/Extra_Fully_Connected_Graphs/edges_700.csv"
                "../Data/Extra_Fully_Connected_Graphs/edges_800.csv"
                "../Data/Extra_Fully_Connected_Graphs/edges_900.csv"
        };

        string nodefilename = "../Data/Extra_Fully_Connected_Graphs/nodes.csv";
        auto nodeMap = util.readNodes(nodefilename);

        for (int i=0; i<11; i++) {
            std::cout << "\nDisplaying data for: " << edgefilenames[i] << std::endl;
            auto edgesMap = util.readEdges(edgefilenames[i]);

            int totalEdges = 0;
            for (const auto& pair : edgesMap) {
                totalEdges += pair.second.size();
            }
            std::cout << "Total number of edges: " << totalEdges << std::endl;

            std::cout << "Total number of nodes: " << nodeMap.size() << std::endl;

        }
    }
};

#endif // MENU_H
