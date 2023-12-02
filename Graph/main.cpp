#include "undirected_graph.hpp"
#include "directed_graph.hpp"

int main(int argc, char const *argv[]) {
    UndirectedGraph<int, int, int> graph;

    graph.insert_vertex(1, 1);
    graph.insert_vertex(2, 2);
    graph.insert_vertex(3, 3);

    graph.insert_edge(1, 2, 12);
    graph.insert_edge(2, 3, 23);
    graph.insert_edge(3, 1, 31);

    graph.display();

    std::cout << "Density: " << graph.density() << std::endl;
    std::cout << "Is dense: " << graph.is_dense() << std::endl;

    graph.remove_edge(1, 2);
    graph.remove_edge(2, 3);
    graph.remove_edge(3, 1);

    graph.remove_vertex(1);

    graph.display();

    return 0;
}
