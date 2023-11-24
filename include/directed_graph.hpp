#pragma once
#include "graph.hpp"
#include <stack>

template<typename TI, typename TV, typename TE>
class DirectedGraph : public Graph<TI, TV, TE> {
public:
    bool add_vertex(TI id, TV vertex) override {
        if (this->vertexes.find(id) != this->vertexes.end()) {
            return false; // Vertex already exists
        }

        // Vertex doesn't exist, so add it
        std::shared_ptr<Vertex<TI, TV, TE>> new_vertex = std::make_shared<Vertex<TI, TV, TE>>();
        new_vertex->id = id;
        new_vertex->data = vertex;
        this->vertexes[id] = new_vertex;

        return true; // Vertex added
    }

    bool add_edge(TI start, TI end, TE edge) override {
        if (this->vertexes.find(start) == this->vertexes.end() ||
            this->vertexes.find(end) == this->vertexes.end()) {
            return false; // Vertex doesn't exist
        }

        // Vertexes exist, so add edge
        std::shared_ptr<Vertex<TI, TV, TE>> start_vertex = this->vertexes[start];
        std::shared_ptr<Vertex<TI, TV, TE>> end_vertex = this->vertexes[end];

        // Check if edge already exists
        if (start_vertex->edges.find(end) != start_vertex->edges.end()) {
            return false; // Edge already exists
        }

        // Edge doesn't exist, so add it
        std::unique_ptr<Edge<TI, TV, TE>> new_edge = std::make_unique<Edge<TI, TV, TE>>();
        new_edge->vertexes[0] = start_vertex;
        new_edge->vertexes[1] = end_vertex;
        new_edge->weight = edge;
        start_vertex->edges[end] = std::move(new_edge); // Add edge

        return true; // Edge added
    }

    bool search_vertex(TI id) override {
        return this->vertexes.find(id) != this->vertexes.end();
    }

    bool search_edge(TI start, TI end) override {
        if (this->vertexes.find(start) == this->vertexes.end() ||
            this->vertexes.find(end) == this->vertexes.end()) {
            return false; // One or both vertexes don't exist
        }

        // Vertexes exist, so search for edge
        return this->vertexes[start]->edges.find(end) != this->vertexes[start]->edges.end();
    }

    bool remove_vertex(TI id) override {
        if (this->vertexes.find(id) == this->vertexes.end()) {
            return false; // Vertex doesn't exist
        }

        // Vertex exists, so remove it
        this->vertexes[id]->edges.clear(); // Remove all edges from vertex to be removed
        this->vertexes.erase(id); // Remove vertex
        
        for (auto& vertex : this->vertexes) {
            if (vertex.second->edges.find(id) != vertex.second->edges.end()) {
                vertex.second->edges.erase(id); // Remove edge from other vertexes to vertex to be removed
            }
        }

        return true; // Vertex removed
    }

    bool remove_edge(TI start, TI end) override {
        if (this->vertexes.find(start) == this->vertexes.end() ||
            this->vertexes.find(end) == this->vertexes.end()) {
            return false; // One or both vertexes don't exist
        }

        // Vertexes exist, so remove edge
        if (this->vertexes[start]->edges.find(end) == this->vertexes[start]->edges.end()) {
            return false; // Edge doesn't exist
        }

        // Edge exists, so remove it
        this->vertexes[start]->edges.erase(end); // Remove edge

        return true; // Edge removed
    }

    TE& operator() (TI start, TI end) override {
        if (this->vertexes.find(start) == this->vertexes.end() ||
            this->vertexes.find(end) == this->vertexes.end()) {
            throw std::out_of_range("One or both vertexes don't exist");
        }

        // Vertexes exist, so return edge
        if (this->vertexes[start]->edges.find(end) == this->vertexes[start]->edges.end()) {
            throw std::out_of_range("Edge doesn't exist");
        }

        // Edge exists, so return it
        return this->vertexes[start]->edges[end]->weight; // Return edge
    }

    float density() override {
        if (this->vertexes.empty()) {
            return 0.0f; // Graph is empty
        }

        // Graph isn't empty, so calculate density
        float density = 0.0f;
        for (auto& vertex : this->vertexes) {
            density += vertex.second->edges.size();
        }
        density /= this->vertexes.size() * (this->vertexes.size() - 1);

        return density; // Return density
    }

    bool is_dense(float threshold = 0.5) override {
        return this->density() >= threshold;
    }

    bool empty() override {
        return this->vertexes.empty();
    }

    void clear() override {
        for (auto& vertex : this->vertexes) {
            vertex.second->edges.clear(); // delete edges
        }
        this->vertexes.clear(); // delete vertexes
    }

    void display() override {
        for (auto& vertex : this->vertexes) {
            std::cout << "Vertex " << vertex.first << " (data: " << vertex.second->data << "):\n";
            if (vertex.second->edges.empty()) { // vertex has no edges
                std::cout << "\tNo edges\n";
            } else { // vertex has edges
                for (auto& edge : vertex.second->edges) {
                    std::cout << "\tEdge to vertex " << edge.first
                              << " with weight " << edge.second->weight << '\n';
                }
            }
        }
    }

    void display_vertex(TI id) override {
        if (this->vertexes.find(id) == this->vertexes.end()) {
            throw std::out_of_range("vertex doesn't exist");
        }
        // vertex exists, so display it
        std::cout << "Vertex " << id << " (data: " << this->vertexes[id]->data << "):\n";
        if (this->vertexes[id]->edges.empty()) { // vertex has no edges
            std::cout << "\tNo edges\n";
        } else { // vertex has edges
            for (auto& edge : this->vertexes[id]->edges) {
                std::cout << "\tEdge to vertex " << edge.first
                          << " with weight " << edge.second->weight << '\n';
            }
        }
    }
};
