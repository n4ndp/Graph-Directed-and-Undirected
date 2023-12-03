#include "../graph.hpp"

template<typename TI, typename TV, typename TE>
std::vector<std::vector<TE>> floyd_warshall(Graph<TI, TV, TE>& graph) {
    auto V = graph.get_vertexes();
    
    auto [index, D] = to_adjacency_matrix(graph); // D = adjacency matrix of graph

    for (int k = 0; k < V.size(); k++) { // for each vertex k
        for (int i = 0; i < V.size(); i++) {
            for (int j = 0; j < V.size(); j++) {
                if (D[i][k] != std::numeric_limits<TE>::max() && D[k][j] != std::numeric_limits<TE>::max() &&
                    D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j]; // update distance from i to j if necessary (through k)
                }
            }
        }
    }

    return D;
}
