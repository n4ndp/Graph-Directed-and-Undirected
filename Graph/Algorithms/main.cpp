#include "../directed_graph.hpp"
#include "bfs.hpp"
#include "dfs.hpp"

void test() {
    DirectedGraph<int, int, int> graph;

    graph.insert_vertex(1, 1);
    graph.insert_vertex(2, 2);
    graph.insert_vertex(3, 3);
    graph.insert_vertex(4, 4);

    graph.insert_edge(1, 2, 1);
    graph.insert_edge(1, 3, 1);
    graph.insert_edge(2, 3, 1);
    graph.insert_edge(3, 1, 1);
    graph.insert_edge(3, 4, 1);
    graph.insert_edge(4, 4, 1);

    auto tree_edges = DFS(graph, 1);

    for (auto& [parent, child] : tree_edges) {
        std::cout << parent << " -> " << child << std::endl;
    }

    std::cout << std::endl;

    tree_edges = BFS(graph, 1);

    for (auto& [parent, child] : tree_edges) {
        std::cout << parent << " -> " << child << std::endl;
    }
}


int main() {
    test();

    return 0;
}
