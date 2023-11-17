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
private:
    std::unordered_map<TI, Vertex<TV, TE>*> vertexes;

public:
    virtual bool add_vertex(TI id, TV vertex) = 0;
    virtual bool add_edge(TI start, TI end, TE edge) = 0;
    virtual bool remove_vertex(TI id) = 0;
    virtual bool remove_edge(TI start, TI end) = 0;
    virtual TE& operator() (TI start, TI end) = 0;
    virtual float density() = 0;
    virtual bool empty() = 0;
    virtual void clear() = 0;
    virtual void display() = 0;
};

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
