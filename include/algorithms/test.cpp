#include "../directed_graph.hpp"
#include "../undirected_graph.hpp"
#include "dijkstra.hpp"
#include "bellman_ford.hpp"

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

    return EXIT_SUCCESS;
}

int test_bellman_ford() {
    DirectedGraph<std::string, std::string, int> graph;

    graph.add_vertex("A", "A");
    graph.add_vertex("B", "B");
    graph.add_vertex("C", "C");
    graph.add_vertex("D", "D");
    graph.add_vertex("E", "E");

    graph.add_edge("A", "B", 6);
    graph.add_edge("A", "C", 7);

    graph.add_edge("B", "C", 8);
    graph.add_edge("B", "D", 5);
    graph.add_edge("B", "E", -4);

    graph.add_edge("C", "D", -3);
    graph.add_edge("C", "E", 9);

    graph.add_edge("D", "B", -2);

    graph.add_edge("E", "D", 7);
    graph.add_edge("E", "A", 2);

    std::string s = "A";
    std::unordered_map<std::string, int> distances = bellman_ford<std::string, std::string, int>(graph, s);

    for (auto& distance : distances) {
        std::cout << "Distance from " << s << " to " << distance.first << " is " << distance.second << std::endl;
    }
    distances.clear();

    return EXIT_FAILURE;
}

int main() {
    //test_dijkstra();
    //test_bellman_ford();

    return EXIT_SUCCESS;
}
