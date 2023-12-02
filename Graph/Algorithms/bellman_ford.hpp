#pragma once
#include "../graph.hpp"
#include <limits>
#include <tuple>
#include <unordered_map>

template<typename TI, typename TV, typename TE>
std::unordered_map<TI, TE> bellman_ford(Graph<TI, TV, TE>& graph, TI start) {
    auto V = graph.get_vertexes();
    std::vector<std::tuple<TI, TI, TE>> E;

    for (auto& [key, vertex] : V) {
        for (auto& [neighbor, edge] : vertex->edges) {
            if (graph) { // directed
                E.push_back(std::make_tuple(vertex->key, neighbor->key, edge->weight));
            } else { // undirected
                if (vertex->key <= neighbor->key) { // only add edge once for undirected graph (avoid duplicates)
                    E.push_back(std::make_tuple(vertex->key, neighbor->key, edge->weight));
                }
            }
        }
    }

    std::unordered_map<TI, TE> distances; // distances from start to each vertex
    for (auto& [key, vertex] : V) {
        distances[key] = std::numeric_limits<TE>::max();
    }
    distances[start] = 0; // distance from start to start is 0

    for (int i = 0; i < V.size() - 1; i++) {
        for (auto& [u, v, weight] : E) {
            if (distances[u] != std::numeric_limits<TE>::max() && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight; // update distance from start to neighbor if necessary
            }
        }
    }

    // check for negative weight cycles
    for (auto& [u, v, w] : E) {
        if (distances[u] != std::numeric_limits<TE>::max() && distances[u] + w < distances[v]) {
            throw std::runtime_error("Graph contains a negative-weight cycle");
        }
    }

    return distances;
}
