#pragma once
#include <limits>

template<typename TI, typename TV, typename TE>
std::unordered_map<TI, TE> bellman_ford(Graph<TI, TV, TE>& graph, TI start) {
    std::unordered_map<TI, std::shared_ptr<Vertex<TI, TV, TE>>> V = graph.get_vertexes();
    std::unordered_map<std::pair<TI, TI>, TE> E = graph.get_edges();

    std::unordered_map<TI, TE> distances; // distances from start to each vertex
    for (auto& vertex : V) {
        distances[vertex.first] = std::numeric_limits<TE>::max(); // distance from start to vertex is infinite
    }
    distances[start] = 0; // distance from start to itself is 0

    for (size_t i = 0; i < V.size() - 1; i++) {
        for (auto& edge : E) { // for each edge (u, v)
            TI u = edge.first.first;
            TI v = edge.first.second;
            TE weight = edge.second; // weight of edge (u, v)

            if (distances[u] + weight < distances[v] && distances[u] != std::numeric_limits<TE>::max()) { // distances[u] != std::numeric_limits<TE>::max() to avoid overflow
                distances[v] = distances[u] + weight; // update distance from start to v
            }
        }
    }

    // check for negative-weight cycles
    for (auto& edge : E) { // for each edge (u, v)
        TI u = edge.first.first;
        TI v = edge.first.second;
        TE weight = edge.second; // weight of edge (u, v)

        if (distances[u] + weight < distances[v] && distances[u] != std::numeric_limits<TE>::max()) { // distances[u] != std::numeric_limits<TE>::max() to avoid overflow
            throw std::runtime_error("Graph contains a negative-weight cycle");
        }
    }

    return distances; // return distances from start to each vertex
}
