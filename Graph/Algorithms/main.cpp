#include "../directed_graph.hpp"
#include "../undirected_graph.hpp"
#include "dijkstra.hpp"
#include "bellman_ford.hpp"
#include "dfs.hpp"
#include "bfs.hpp"

int test_dfs() {
    UndirectedGraph<std::string, std::string, int> graph;

    graph.insert_vertex("A", "A");
    graph.insert_vertex("B", "B");
    graph.insert_vertex("C", "C");
    graph.insert_vertex("D", "D");
    graph.insert_vertex("E", "E");
    graph.insert_vertex("F", "F");
    graph.insert_vertex("G", "G");
    graph.insert_vertex("H", "H");
    graph.insert_vertex("I", "I");

    graph.insert_edge("A", "E", 1);
    graph.insert_edge("A", "C", 1);
    graph.insert_edge("A", "B", 1);

    graph.insert_edge("B", "D", 1);
    graph.insert_edge("B", "C", 1);
    
    graph.insert_edge("C", "D", 1);
    graph.insert_edge("C", "E", 1);
    graph.insert_edge("C", "F", 1);

    graph.insert_edge("E", "H", 1);
    graph.insert_edge("E", "G", 1);

    graph.insert_edge("G", "I", 1);

    graph.insert_edge("H", "I", 1);

    std::string s = "A";
    std::vector<std::pair<std::string, std::string>> tree_edges = DFS<std::string, std::string, int>(graph, s);
    for (auto& edge : tree_edges) {
        std::cout << edge.first << " -> " << edge.second << std::endl;
    }
    tree_edges.clear();

    return EXIT_SUCCESS;
}

int test_bfs() {
    UndirectedGraph<std::string, std::string, int> graph;

    graph.insert_vertex("A", "A");
    graph.insert_vertex("B", "B");
    graph.insert_vertex("C", "C");
    graph.insert_vertex("D", "D");
    graph.insert_vertex("E", "E");
    graph.insert_vertex("F", "F");
    graph.insert_vertex("G", "G");
    graph.insert_vertex("H", "H");
    graph.insert_vertex("I", "I");

    graph.insert_edge("A", "E", 1);
    graph.insert_edge("A", "C", 1);
    graph.insert_edge("A", "B", 1);

    graph.insert_edge("B", "D", 1);
    graph.insert_edge("B", "C", 1);
    
    graph.insert_edge("C", "D", 1);
    graph.insert_edge("C", "E", 1);
    graph.insert_edge("C", "F", 1);

    graph.insert_edge("E", "H", 1);
    graph.insert_edge("E", "G", 1);

    graph.insert_edge("G", "I", 1);

    graph.insert_edge("H", "I", 1);

    std::string s = "A";
    std::vector<std::pair<std::string, std::string>> tree_edges = BFS<std::string, std::string, int>(graph, s);
    for (auto& edge : tree_edges) {
        std::cout << edge.first << " -> " << edge.second << std::endl;
    }
    tree_edges.clear();

    return EXIT_SUCCESS;
}

int test_dijkstra() {
    DirectedGraph<std::string, std::string, int> graph;

    graph.insert_vertex("A", "A");
    graph.insert_vertex("B", "B");
    graph.insert_vertex("C", "C");
    graph.insert_vertex("D", "D");
    graph.insert_vertex("E", "E");

    graph.insert_edge("A", "B", 4);
    graph.insert_edge("A", "C", 2);

    graph.insert_edge("B", "C", 3);
    graph.insert_edge("B", "D", 2);
    graph.insert_edge("B", "E", 3);

    graph.insert_edge("C", "B", 1);
    graph.insert_edge("C", "D", 4);
    graph.insert_edge("C", "E", 5);

    graph.insert_edge("E", "D", 1);

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

    graph.insert_vertex("A", "A");
    graph.insert_vertex("B", "B");
    graph.insert_vertex("C", "C");
    graph.insert_vertex("D", "D");
    graph.insert_vertex("E", "E");

    graph.insert_edge("A", "B", 6);
    graph.insert_edge("A", "C", 7);

    graph.insert_edge("B", "C", 8);
    graph.insert_edge("B", "D", 5);
    graph.insert_edge("B", "E", -4);

    graph.insert_edge("C", "D", -3);
    graph.insert_edge("C", "E", 9);

    graph.insert_edge("D", "B", -2);

    graph.insert_edge("E", "D", 7);
    graph.insert_edge("E", "A", 2);

    std::string s = "A";
    std::unordered_map<std::string, int> distances = bellman_ford<std::string, std::string, int>(graph, s);
    for (auto& distance : distances) {
        std::cout << "Distance from " << s << " to " << distance.first << " is " << distance.second << std::endl;
    }
    distances.clear();

    return EXIT_SUCCESS;
}

int main() {
    test_dfs();
    std::cout << std::endl;
    test_bfs();
    std::cout << std::endl;
    test_dijkstra();
    std::cout << std::endl;
    test_bellman_ford();

    return 0;
}
