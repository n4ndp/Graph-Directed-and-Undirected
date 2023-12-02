#pragma once
#include "../graph.hpp"
#include <queue>
#include <unordered_set>
#include <limits>

template<typename TI, typename TV, typename TE>
std::vector<std::pair<TI, TI>> BFS(Graph<TI, TV, TE>& graph, TI start) {
    auto V = graph.get_vertexes();
    std::unordered_set<TI> visited;
    std::queue<TI> queue;

    std::vector<std::pair<TI, TI>> tree_edges; // (parent, child) pairs

    queue.push(start); // enqueue the start vertex
    visited.insert(start); // mark the start vertex as visited

    while (!queue.empty()) {
        TI current = queue.front();
        queue.pop();

        for (auto& [neighbor, edge] : V[current]->edges) {
            if (visited.find(neighbor->key) == visited.end()) { // if neighbor is not visited
                queue.push(neighbor->key);
                visited.insert(neighbor->key);
                tree_edges.push_back(std::make_pair(current, neighbor->key));
            }
        }
    }

    return tree_edges;
};
