#pragma once
#include "../graph.hpp"
#include <unordered_set>
#include <vector>
#include <limits>

template<typename TI, typename TV, typename TE>
void DFS(Graph<TI, TV, TE>& graph, TI start, std::unordered_set<TI>& visited, std::vector<std::pair<TI, TI>>& tree_edges, std::unordered_map<TI, std::shared_ptr<Vertex<TI, TV, TE>>>& V) {
    visited.insert(start); // mark the vertex as visited

    for (auto& edge : V[start]->edges) {
        TI neighbor = edge.second->vertexes[1]->id; // get the neighbor of the current vertex

        if (visited.find(neighbor) == visited.end()) { // if the neighbor has not been visited yet
            tree_edges.emplace_back(start, neighbor); // add the edge to the tree edges
            DFS(graph, neighbor, visited, tree_edges, V); // recursively call DFS on the neighbor vertex to explore its neighbors
        }
    } // when the neighbor has no more neighbors, the function will return and the next neighbor will be explored
}

template<typename TI, typename TV, typename TE>
std::vector<std::pair<TI, TI>> DFS(Graph<TI, TV, TE>& graph, TI start) {
    std::unordered_map<TI, std::shared_ptr<Vertex<TI, TV, TE>>> V = graph.get_vertexes();
    std::unordered_set<TI> visited;
    std::vector<std::pair<TI, TI>> tree_edges; // (parent, child) pairs

    DFS(graph, start, visited, tree_edges, V); // call the recursive DFS function

    return tree_edges; // return the tree edges of the DFS tree
}
