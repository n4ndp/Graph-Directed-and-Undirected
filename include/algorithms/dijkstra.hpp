#pragma once
#include "../graph.hpp"
#include <unordered_set>
#include <vector>
#include <limits>
#include <queue>

template<typename TI, typename TV, typename TE> // secuential
std::unordered_map<TI, TE> dijkstra_secuential(Graph<TI, TV, TE>& graph, TI start) {
    std::unordered_map<TI, std::shared_ptr<Vertex<TI, TV, TE>>> V = graph.get_vertexes();

    std::unordered_map<TI, TE> distances; // distances from start to each vertex
    for (auto& vertex : V) {
        distances[vertex.first] = std::numeric_limits<TE>::max(); // distance from start to vertex is infinite
    }
    distances[start] = 0; // distance from start to itself is 0

    std::unordered_set<TI> R;
    for (auto& vertex : V) {
        R.insert(vertex.first);
    } // R is V initially

    while (!R.empty()) {
        TI min_vertex = *R.begin();
        for (auto& vertex : R) { // secuential search
            if (distances[vertex] < distances[min_vertex]) {
                min_vertex = vertex; // find vertex with minimum distance in R
            }
        }
        R.erase(min_vertex); // remove min_vertex from R

        for (auto& edge : V[min_vertex]->edges) { // for each edge (min_vertex, x)
            TI x = edge.second->vertexes[1]->id;
            if (distances[min_vertex] + edge.second->weight < distances[x]) {
                distances[x] = distances[min_vertex] + edge.second->weight; // update distance from start to x
            }
        }
    }

    return distances; // return distances from start to each vertex
}

template<typename TI, typename TV, typename TE> // priority queue
std::unordered_map<TI, TE> dijkstra_priority_queue(Graph<TI, TV, TE>& graph, TI start) {
    std::unordered_map<TI, std::shared_ptr<Vertex<TI, TV, TE>>> V = graph.get_vertexes();

    std::unordered_map<TI, TE> distances; // distances from start to each vertex
    for (auto& vertex : V) {
        distances[vertex.first] = std::numeric_limits<TE>::max(); // distance from start to vertex is infinite
    }
    distances[start] = 0; // distance from start to itself is 0

    std::priority_queue<std::pair<TE, TI>, std::vector<std::pair<TE, TI>>, std::greater<std::pair<TE, TI>>> Q;
    for (auto& vertex : V) {
        Q.push(std::make_pair(distances[vertex.first], vertex.first)); // Q is a priority queue of pairs (distance, vertex)
    } // Q is V initially

    while (!Q.empty()) {
        TI min_vertex = Q.top().second;
        Q.pop(); // remove min_vertex from Q

        for (auto& edge : V[min_vertex]->edges) { // for each edge (min_vertex, x)
            TI x = edge.second->vertexes[1]->id;
            if (distances[min_vertex] + edge.second->weight < distances[x]) {
                distances[x] = distances[min_vertex] + edge.second->weight; // update distance from start to x
                Q.push(std::make_pair(distances[x], x)); // add (distance, x) to Q
            }
        }
    }

    return distances; // return distances from start to each vertex
}
