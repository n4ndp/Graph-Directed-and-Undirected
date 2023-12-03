#include "../directed_graph.hpp"
#include "floyd_warshall.hpp"

int main() {
    DirectedGraph<int, int, int> graph;

    graph.insert_vertex(5, 5);
    graph.insert_vertex(4, 4);
    graph.insert_vertex(3, 3);
    graph.insert_vertex(2, 2);
    graph.insert_vertex(1, 1);

    graph.insert_edge(1, 2, 3);
    graph.insert_edge(1, 3, 8);
    graph.insert_edge(1, 5, -4);

    graph.insert_edge(2, 4, 1);
    graph.insert_edge(2, 5, 7);

    graph.insert_edge(3, 2, 4);

    graph.insert_edge(4, 1, 2);
    graph.insert_edge(4, 3, -5);

    graph.insert_edge(5, 4, 6);

    /*auto [index, matrix] = to_adjacency_matrix(graph);

    for (auto& row : matrix) {
        for (auto& col : row) {
            if (col == std::numeric_limits<int>::max()) {
                std::cout << "\tinf ";
            } else {
                std::cout << "\t" << col << " ";
            }
        }
        std::cout << std::endl;
    }*/

    auto matrix = floyd_warshall(graph);

    for (auto& row : matrix) {
        for (auto& col : row) {
            if (col == std::numeric_limits<int>::max()) {
                std::cout << "\tinf ";
            } else {
                std::cout << "\t" << col << " ";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}
