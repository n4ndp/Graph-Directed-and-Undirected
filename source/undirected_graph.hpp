#include "graph.hpp"
/* in graph.hpp:
#pragma once
#include <iostream>
#include <unordered_map>
#include <list>

template<typename TV, typename TE>
struct Edge;

template<typename TV, typename TE>
struct Vertex;

template<typename TID, typename TV, typename TE>
class Graph {
private:
    std::unordered_map<TID, Vertex<TV, TE>*> vertexes;

public:
    virtual bool add_vertex(TID id, TV vertex) = 0;
    virtual bool add_edge(TID start, TID end, TE edge) = 0;
    virtual bool remove_vertex(TID id) = 0;
    virtual bool remove_edge(TID start, TID end) = 0;
    virtual TE& operator() (TID start, TID end) = 0;
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
*/

template<typename TV, typename TE>
class UndirectedGraph : public Graph<TV, TE> {};



