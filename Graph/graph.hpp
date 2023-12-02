#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>

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
};
