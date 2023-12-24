#pragma once
#include "../graph.hpp"
#include <unordered_set>
#include <limits>

template<typename TI, typename TV, typename TE>
void DFS_visit(Graph<TI, TV, TE>& graph, TI current, std::unordered_set<TI>& visited, std::vector<std::pair<TI, TI>>& tree_edges) {
    visited.insert(current);

    for (auto& [neighbor, edge] : graph.get_vertexes()[current]->edges) {
        if (visited.find(neighbor->key) == visited.end()) { // if neighbor is not visited
            tree_edges.push_back(std::make_pair(current, neighbor->key));
            DFS_visit(graph, neighbor->key, visited, tree_edges);
        }
    }
}

template<typename TI, typename TV, typename TE>
std::vector<std::pair<TI, TI>> DFS(Graph<TI, TV, TE>& graph, TI start) {
    std::unordered_set<TI> visited;
    std::vector<std::pair<TI, TI>> tree_edges; // (parent, child) pairs

    DFS_visit(graph, start, visited, tree_edges);

    return tree_edges;
};
