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

template<typename TI, typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE> {
public:
    bool add_vertex(TI id, TV vertex) {
        if (this->vertexes.find(id) != this->vertexes.end()) {
            return false; // vertex already exists
        }
        // vertex doesn't exist, so add it
        Vertex<TV, TE>* new_vertex = new Vertex<TV, TE>;
        new_vertex->data = vertex;
        this->vertexes[id] = new_vertex;

        return true; // vertex added
    }

    bool add_edge(TI start, TI end, TE edge) {
        if (this->vertexes.find(start) == this->vertexes.end() || this->vertexes.find(end) == this->vertexes.end()) {
            return false; // one or both vertexes don't exist
        }
        // vertexes exist, so add edge
        Edge<TV, TE>* new_edge = new Edge<TV, TE>;
        new_edge->vertexes[0] = this->vertexes[start];
        new_edge->vertexes[1] = this->vertexes[end];
        new_edge->weight = edge;
        this->vertexes[start]->edges[this->vertexes[end]] = new_edge; // add edge to start vertex

        return true; // edge added
    }

    bool remove_vertex(TI id) {
        if (this->vertexes.find(id) == this->vertexes.end()) {
            return false; // vertex doesn't exist
        }
        // vertex exists, so remove it
        for (auto& vertex : this->vertexes) {
            if (vertex.second->edges.find(this->vertexes[id]) != vertex.second->edges.end()) {
                // vertex has an edge to the vertex to be removed
                vertex.second->edges.erase(this->vertexes[id]); // remove edge
            }
        }
        delete this->vertexes[id]; // delete vertex
        this->vertexes.erase(id); // remove vertex from map

        return true; // vertex removed
    }

    bool remove_edge(TI start, TI end) {
        if (this->vertexes.find(start) == this->vertexes.end() || this->vertexes.find(end) == this->vertexes.end()) {
            return false; // one or both vertexes don't exist
        }
        // vertexes exist, so remove edge
        if (this->vertexes[start]->edges.find(this->vertexes[end]) == this->vertexes[start]->edges.end()) {
            return false; // edge doesn't exist
        }
        // edge exists, so remove it
        delete this->vertexes[start]->edges[this->vertexes[end]]; // delete edge
        this->vertexes[start]->edges.erase(this->vertexes[end]); // remove edge from map

        return true; // edge removed
    }

    TE& operator() (TI start, TI end) {
        if (this->vertexes.find(start) == this->vertexes.end() || this->vertexes.find(end) == this->vertexes.end()) {
            throw std::out_of_range("one or both vertexes don't exist");
        }
        // vertexes exist, so return edge
        if (this->vertexes[start]->edges.find(this->vertexes[end]) == this->vertexes[start]->edges.end()) {
            throw std::out_of_range("edge doesn't exist");
        }
        // edge exists, so return it
        return this->vertexes[start]->edges[this->vertexes[end]]->weight; // return edge
    }

    float density() {
        if (this->vertexes.empty()) {
            return 0.0f; // graph is empty
        }
        // graph isn't empty, so calculate density
        int num_edges = 0;
        for (auto& vertex : this->vertexes) {
            num_edges += vertex.second->edges.size();
        }
        return (float)num_edges / (float)this->vertexes.size(); // return density
    }

    bool empty() {
        return this->vertexes.empty(); // return whether graph is empty
    }

    void clear() {
        for (auto& vertex : this->vertexes) {
            delete vertex.second; // delete vertex
        }
        this->vertexes.clear(); // clear map
    }

    void display() {
        for (auto& vertex : this->vertexes) {
            std::cout << vertex.first << ": ";
            for (auto& edge : vertex.second->edges) {
                std::cout << edge.first->data << " ";
            }
            std::cout << std::endl;
        }
    }
};
