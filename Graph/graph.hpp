#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <tuple>

template<typename TI, typename TV, typename TE>
class Graph {
protected:
    struct Edge;
    struct Vertex;
    
    struct Edge {
        TE weight;
        std::shared_ptr<Vertex> vertexes[2];
    };

    struct Vertex {
        TI key;
        TV value;
        std::unordered_map<std::shared_ptr<Vertex>, std::unique_ptr<Edge>> edges;
    };

    std::unordered_map<TI, std::shared_ptr<Vertex>> vertexes;

public:
    virtual bool insert_vertex(TI key, TV value) = 0;
    virtual bool insert_edge(TI start, TI end, TE weight) = 0;
    virtual bool remove_vertex(TI key) = 0;
    virtual bool remove_edge(TI start, TI end) = 0;

    virtual TE& operator() (TI start, TI end) = 0;
    virtual operator bool() const = 0; // true if graph is directed, false if graph is undirected
    virtual float density() = 0;
    virtual bool is_dense(float threshold = 0.5) = 0;
    virtual bool empty() = 0;
    virtual void clear() = 0;
    virtual void display() = 0;

    std::unordered_map<TI, std::shared_ptr<Vertex>>& get_vertexes() {
        return vertexes;
    }
};

template<typename TI, typename TV, typename TE>
std::tuple<std::unordered_map<TI, int>, std::vector<std::vector<TE>>> to_adjacency_matrix(Graph<TI, TV, TE>& graph) {
    auto V = graph.get_vertexes();
    std::unordered_map<TI, int> index; // index of vertex in matrix (row/column)
    int i = 0;
    for (auto& [key, vertex] : V) {
        index[key] = i;
        i++;
    }
    std::vector<std::vector<TE>> matrix(V.size(), std::vector<TE>(V.size(), std::numeric_limits<TE>::max())); // adjacency matrix
    for (int i = 0; i < V.size(); i++) {
        matrix[i][i] = 0.0f; // distance from vertex to itself is 0
    }

    for (auto& [key, vertex] : V) {
        for (auto& [neighbor, edge] : vertex->edges) {
            matrix[index[key]][index[neighbor->key]] = edge->weight; // distance from vertex to neighbor is weight of edge
        }
    }

    return std::make_tuple(index, matrix);
}
