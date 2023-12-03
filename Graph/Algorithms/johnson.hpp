#include "../graph.hpp"
#include "bellman_ford.hpp"
#include "utilities/random_all.hpp"

template<typename TI, typename TV, typename TE>
std::vector<std::vector<TE>> jhonson(Graph<TI, TV, TE>& graph) {
    auto V = graph.get_vertexes();

    // Add new vertex s to graph and add edges from s to all other vertexes with weight 0
    TI s =  random_value<TI>();
    // Verify that s is not already a key in the graph
    while (V.find(s) != V.end()) {
        s = random_value<TI>();
    }
    std::cout << "s = " << s << std::endl;

    graph.insert_vertex(s, TV()); // s = new vertex
    for (auto& [key, vertex] : V) {
        graph.insert_edge(s, key, 0); // add edge from s to all other vertexes
    }

    auto h = bellman_ford(graph, s); // h = distance from s to all other vertexes
    graph.remove_vertex(s); // remove s from graph

    //...
}
