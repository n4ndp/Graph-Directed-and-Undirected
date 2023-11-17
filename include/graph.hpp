#pragma once
#include <iostream>
#include <unordered_map>
#include <list>

template<typename TV, typename TE>
struct Edge;

template<typename TV, typename TE>
struct Vertex;

template<typename TI, typename TV, typename TE>
class Graph {
protected:
    std::unordered_map<TI, Vertex<TV, TE>*> vertexes;

public:
    virtual bool add_vertex(TI id, TV vertex) = 0;
    virtual bool add_edge(TI start, TI end, TE edge) = 0;
    virtual bool search_vertex(TI id) = 0;
    virtual bool search_edge(TI start, TI end) = 0;
    virtual bool remove_vertex(TI id) = 0;
    virtual bool remove_edge(TI start, TI end) = 0;
    virtual TE& operator() (TI start, TI end) = 0;
    virtual float density() = 0;
    virtual bool is_dense(float threshold = 0.5) = 0;
    virtual bool empty() = 0;
    virtual void clear() = 0;
    virtual void display() = 0;
    virtual void display_vertex(TI id) = 0;
    std::unordered_map<TI, Vertex<TV, TE>*> get_vertexes() const;
    size_t sizev();
    size_t sizee();
};

template<typename TI, typename TV, typename TE>
std::unordered_map<TI, Vertex<TV, TE>*> Graph<TI, TV, TE>::get_vertexes() const {
    return this->vertexes;
}

template<typename TI, typename TV, typename TE>
size_t Graph<TI, TV, TE>::sizev() { // number of vertexes
    return this->vertexes.size();
}

template<typename TI, typename TV, typename TE>
size_t Graph<TI, TV, TE>::sizee() { // number of edges
    size_t size = 0;
    for (auto& vertex : this->vertexes) {
        size += vertex.second->edges.size();
    }
    return size;
}

template<typename TV, typename TE>
struct Edge {
    Vertex<TV, TE>* vertexes[2];
    TE weight;
};

template<typename TV, typename TE>
struct Vertex {
    TV data;
    std::unordered_map<Vertex<TV, TE>*, Edge<TV, TE>*> edges;
};
