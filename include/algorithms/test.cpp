#include "dijkstra.hpp"
#include "../directed_graph.hpp"
#include "../undirected_graph.hpp"

int test_dijkstra() {
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

    std::unordered_map<std::string, int> distances = dijkstra_priority_queue<std::string, std::string, int>(graph, s);
    for (auto& distance : distances) {
        std::cout << "Distance from " << s << " to " << distance.first << " is " << distance.second << std::endl;
    }
    distances.clear();

    std::cout << std::endl;

    distances = dijkstra_secuential<std::string, std::string, int>(graph, s);
    for (auto& distance : distances) {
        std::cout << "Distance from " << s << " to " << distance.first << " is " << distance.second << std::endl;
    }
    distances.clear();

    return 0;
}
