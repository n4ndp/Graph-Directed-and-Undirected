#pragma once
#include "../graph.hpp"
#include <limits>
#include <set>

template<typename TI, typename TV, typename TE>
std::unordered_map<TI, TE> dijkstra(Graph<TI, TV, TE>& graph, TI start) {
    std::unordered_map<TI, std::shared_ptr<Vertex<TI, TV, TE>>> V = graph.get_vertexes();

    std::unordered_map<TI, TE> distances; // distances from start to each vertex
    for (auto& vertex : V) {
        distances[vertex.first] = std::numeric_limits<TE>::max(); // distance from start to vertex is infinite
    }
    distances[start] = 0; // distance from start to itself is 0

    std::set<TI> R;
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

/*
int main(int argc, char const *argv[]) {
    DirectedGraph<std::string, std::string, int> graph;

    graph.add_vertex("A", "A");
    graph.add_vertex("B", "B");
    graph.add_vertex("C", "C");
    graph.add_vertex("D", "D");
    graph.add_vertex("E", "E");

    graph.add_edge("A", "B", 4);
    graph.add_edge("A", "C", 2);

    graph.add_edge("B", "C", 3);
    graph.add_edge("B", "D", 2);
    graph.add_edge("B", "E", 3);

    graph.add_edge("C", "B", 1);
    graph.add_edge("C", "D", 4);
    graph.add_edge("C", "E", 5);

    graph.add_edge("E", "D", 1);

    std::string s = "A";
    std::unordered_map<std::string, int> distances = dijkstra<std::string, std::string, int>(graph, s);

    for (auto& distance : distances) {
        std::cout << "Distance from " << s << " to " << distance.first << " is " << distance.second << std::endl;
    }

    return 0;
}
*/