#pragma once
#include "../graph.hpp"
#include <unordered_set>
#include <vector>
#include <limits>
#include <queue>

template<typename TI, typename TV, typename TE>
std::vector<std::pair<TI, TI>> BFS(Graph<TI, TV, TE>& graph, TI start) {
    std::unordered_map<TI, std::shared_ptr<Vertex<TI, TV, TE>>> V = graph.get_vertexes();
    std::unordered_set<TI> visited;
    std::vector<std::pair<TI, TI>> tree_edges; // (parent, child) pairs
    std::queue<TI> Q;

    Q.push(start); // enqueue the start vertex
    visited.insert(start); // mark the start vertex as visited

    while (!Q.empty()) {
        TI current = Q.front();
        Q.pop();

        for (auto& edge : V[current]->edges) {
            TI neighbor = edge.second->vertexes[1]->id; // get the neighbor of the current vertex
            if (visited.find(neighbor) == visited.end()) { // if the neighbor has not been visited
                visited.insert(neighbor); // mark the neighbor as visited
                tree_edges.push_back(std::make_pair(current, neighbor)); // add the edge to the tree edges
                Q.push(neighbor); // enqueue the neighbor
            }
        } // when all the neighbors of the current vertex have been visited, visit the next available vertex
    }

    return tree_edges; // return the tree edges of the BFS tree
}
