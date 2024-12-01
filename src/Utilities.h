/*
 Conteúdo:
 - readEdge_s(const std::string& filename)
 - readNodes(const std::string& filename)
 - createGraphFromEdge_Map(const std::unordered_map<int, std::vector<Edge_>>& edgesMap)
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "Edge.h"
#include "Graph.h"
#include "Node.h"


class Utilities {
public:
    static std::unordered_map<int, std::vector<Edge_>> readEdges(const std::string& filename) {
        std::unordered_map<int, std::vector<Edge_>> edgeMap;
        std::ifstream file(filename);
        std::string line;

        if (!file.is_open()) {
            std::cerr << "Não foi possível abrir o arquivo: " << filename << std::endl;
            return edgeMap;  // Retorna um mapa vazio se o arquivo não abrir
        }

        // Lê a linha de cabeçalho para descartar
        std::getline(file, line);

        // Lê cada linha subsequente que representa uma aresta
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            int origin, destination;
            double distance;

            if (ss >> origin && ss.ignore() && ss >> destination && ss.ignore() && ss >> distance) {
                Edge_ edge(origin, destination, distance);
                edgeMap[origin].push_back(edge);
                // Se for para armazenar para grafos não direcionados duas vezes, metemos a linha abaixo
                edgeMap[destination].push_back(edge.reverse());
            }
        }

        file.close();
        return edgeMap;
    }

    static std::unordered_map<int, Node> readNodes(const std::string& filename) {
        std::unordered_map<int, Node> nodeMap;
        std::ifstream file(filename);
        std::string line;

        if (!file.is_open()) {
            std::cerr << "Não foi possível abrir o arquivo: " << filename << std::endl;
            return nodeMap;
        }

        std::getline(file, line);
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            int id;
            double longitude, latitude;

            if (ss >> id && ss.ignore() && ss >> longitude && ss.ignore() && ss >> latitude) {
                Node node(id, longitude, latitude);
                nodeMap[id] = node;
            }
        }
        file.close();
        return nodeMap;
    }

    template <typename T>
    static Graph<T>* createGraphFromEdgeMap(const std::unordered_map<int, std::vector<Edge_>>& edgesMap) {
        Graph<T>* graph = new Graph<T>();

        for (const auto& entry : edgesMap) {
            int origin = entry.first;
            graph->addVertex(origin);

            for (const auto& edge : entry.second) {
                int destination = edge.getDestination();
                double distance = edge.getDistance();
                graph->addVertex(destination);
                graph->addEdge(origin, destination, distance);
            }
        }
        return graph;
    }
};

#endif // UTILITIES_H
