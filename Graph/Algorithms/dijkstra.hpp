#include "../graph.hpp"
#include <unordered_set>
#include <limits>
#include <queue>

template<typename TI, typename TV, typename TE> // secuential
std::unordered_map<TI, TE> dijkstra_secuential(Graph<TI, TV, TE>& graph, TI start) {
    auto V = graph.get_vertexes();

    std::unordered_map<TI, TE> distances; // distances from start to each vertex
    for (auto& [key, vertex] : V) {
        distances[key] = std::numeric_limits<TE>::max();
    }
    distances[start] = 0; // distance from start to start is 0

    std::unordered_set<TI> R;
    for (auto& [key, vertex] : V) {
        R.insert(key);
    } // R = V initially

    while (!R.empty()) {
        TI min_vertex = *R.begin();
        for (auto& key : R) { // secuential search
            if (distances[key] < distances[min_vertex]) {
                min_vertex = key; // find vertex with minimum distance in R
            }
        }
        R.erase(min_vertex); // remove min_vertex from R

        for (auto& [neighbor, edge] : V[min_vertex]->edges) { // for each neighbor of min_vertex
            if (distances[min_vertex] + edge->weight < distances[neighbor->key]) {
                distances[neighbor->key] = distances[min_vertex] + edge->weight; // update distance from start to neighbor if necessary
            }
        }
    }

    return distances;
}

template<typename TI, typename TV, typename TE> // priority queue
std::unordered_map<TI, TE> dijkstra_priority_queue(Graph<TI, TV, TE>& graph, TI start) {
    auto V = graph.get_vertexes();

    std::unordered_map<TI, TE> distances; // distances from start to each vertex
    for (auto& [key, vertex] : V) {
        distances[key] = std::numeric_limits<TE>::max();
    }
    distances[start] = 0; // distance from start to start is 0

    std::priority_queue<std::pair<TE, TI>, std::vector<std::pair<TE, TI>>, std::greater<std::pair<TE, TI>>> priority_queue;
    for (auto& [key, vertex] : V) {
        priority_queue.push({ distances[key], key });
    } // priority_queue = V initially

    while (!priority_queue.empty()) {
        TI min_vertex = priority_queue.top().second;
        priority_queue.pop(); // remove min_vertex from priority_queue

        for (auto& [neighbor, edge] : V[min_vertex]->edges) { // for each neighbor of min_vertex
            if (distances[min_vertex] + edge->weight < distances[neighbor->key]) {
                distances[neighbor->key] = distances[min_vertex] + edge->weight; // update distance from start to neighbor if necessary
                priority_queue.push({ distances[neighbor->key], neighbor->key }); // add neighbor to priority_queue
            }
        }
    }

    return distances;
}
