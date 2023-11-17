#pragma once
#include "graph.hpp"
#include <stack>

template<typename TI, typename TV, typename TE>
class UndirectedGraph : public Graph<TI, TV, TE> {
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
        if (this->vertexes.find(start) == this->vertexes.end() ||
            this->vertexes.find(end) == this->vertexes.end()) {
            return false; // vertex doesn't exist
        }
        // vertexes exist, so add edge
        Vertex<TV, TE>* start_vertex = this->vertexes[start];
        Vertex<TV, TE>* end_vertex = this->vertexes[end];

        // check if edge already exists
        if (start_vertex->edges.find(end_vertex) != start_vertex->edges.end()) {
            return false; // edge already exists
        }
        // edge doesn't exist, so add it
        Edge<TV, TE>* new_edge = new Edge<TV, TE>;
        new_edge->vertexes[0] = start_vertex;
        new_edge->vertexes[1] = end_vertex;
        new_edge->weight = edge;
        start_vertex->edges[end_vertex] = new_edge;
        end_vertex->edges[start_vertex] = new_edge;

        return true; // edge added
    }

    bool search_vertex(TI id) {
        return this->vertexes.find(id) != this->vertexes.end();
    }

    bool search_edge(TI start, TI end) {
        if (this->vertexes.find(start) == this->vertexes.end() ||
            this->vertexes.find(end) == this->vertexes.end()) {
            return false; // one or both vertexes don't exist
        }
        // vertexes exist, so search for edge
        return this->vertexes[start]->edges.find(this->vertexes[end]) != this->vertexes[start]->edges.end();
    }

    bool remove_vertex(TI id) {
        if (this->vertexes.find(id) == this->vertexes.end()) {
            return false; // vertex doesn't exist
        }
        // vertex exists, so remove it
        for (auto& vertex : this->vertexes) {
            if (vertex.second->edges.find(this->vertexes[id]) != vertex.second->edges.end()) {
                // vertex has an edge to the vertex to be removed
                // remove edge
                delete vertex.second->edges[this->vertexes[id]];
                vertex.second->edges.erase(this->vertexes[id]);
            }
        }

        delete this->vertexes[id]; // delete vertex
        this->vertexes.erase(id); // remove vertex from map

        return true; // vertex removed
    }

    bool remove_edge(TI start, TI end) {
        if (this->vertexes.find(start) == this->vertexes.end() ||
            this->vertexes.find(end) == this->vertexes.end()) {
            return false; // one or both vertexes don't exist
        }
        // vertexes exist, so remove edge
        if (this->vertexes[start]->edges.find(this->vertexes[end]) == this->vertexes[start]->edges.end()) {
            return false; // edge doesn't exist
        }
        // edge exists, so remove it from both vertexes
        delete this->vertexes[start]->edges[this->vertexes[end]]; // delete edge
        this->vertexes[start]->edges.erase(this->vertexes[end]); // remove edge from map
        delete this->vertexes[end]->edges[this->vertexes[start]]; // delete edge
        this->vertexes[end]->edges.erase(this->vertexes[start]); // remove edge from map

        return true; // edge removed
    }

    TE& operator() (TI start, TI end) {
        if (this->vertexes.find(start) == this->vertexes.end() || 
            this->vertexes.find(end) == this->vertexes.end()) {
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
        float density = 0.0f;
        for (auto& vertex : this->vertexes) {
            density += vertex.second->edges.size();
        }
        density /= this->vertexes.size() * (this->vertexes.size() - 1);

        return density; // return density
    }

    bool is_dense(float threshold = 0.5) {
        return this->density() >= threshold;
    }
    
    bool empty() {
        return this->vertexes.empty();
    }

    void clear() {
        for (auto& vertex : this->vertexes) {
            for (auto& edge : vertex.second->edges) {
                delete edge.second;
            }
            delete vertex.second;
        }
        this->vertexes.clear();
    }

    void display() {
        for (auto& vertex : this->vertexes) {
            std::cout << "Vertex " << vertex.first << " (data: " << vertex.second->data << "):\n";
            if (vertex.second->edges.empty()) { // vertex has no edges
                std::cout << "\tNo edges\n";
            } else { // vertex has edges
                for (auto& edge : vertex.second->edges) {
                    TI id2;
                    for (auto& vertex2 : this->vertexes) {
                        if (vertex2.second == edge.first) {
                            id2 = vertex2.first;
                            break;
                        }
                    }
                    std::cout << "\tEdge to vertex " << id2 << " (data: " 
                              << edge.first->data << ") with weight " 
                              << edge.second->weight << '\n';
                }
            }
        }
    }

    void display_vertex(TI id) {
        if (this->vertexes.find(id) == this->vertexes.end()) {
            throw std::out_of_range("vertex doesn't exist");
        }
        // vertex exists, so display it
        std::cout << "Vertex " << id << " (data: " << this->vertexes[id]->data << "):\n";
        if (this->vertexes[id]->edges.empty()) { // vertex has no edges
            std::cout << "\tNo edges\n";
        } else { // vertex has edges
            for (auto& edge : this->vertexes[id]->edges) {
                TI id2;
                for (auto& vertex : this->vertexes) {
                    if (vertex.second == edge.first) {
                        id2 = vertex.first;
                        break;
                    }
                }
                std::cout << "\tEdge to vertex " << id2 << " (data: " 
                          << edge.first->data << ") with weight " 
                          << edge.second->weight << '\n';
            }
        }
    }
};
