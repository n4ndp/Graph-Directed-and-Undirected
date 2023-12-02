#pragma once
#include "graph.hpp"

template<typename TI, typename TV, typename TE>
class UndirectedGraph : public Graph<TI, TV, TE> {
private:
    using Edge = typename Graph<TI, TV, TE>::Edge;
    using Vertex = typename Graph<TI, TV, TE>::Vertex;
public:
    bool insert_vertex(TI key, TV value) override {
        if (this->vertexes.find(key) != this->vertexes.end()) {
            return false; // Vertex already exists
        }

        // Vertex doesn't exist, so add it
        std::shared_ptr<Vertex> new_vertex = std::make_shared<Vertex>();
        new_vertex->key = key;
        new_vertex->value = value;
        this->vertexes[key] = new_vertex;

        return true;
    }

    bool insert_edge(TI start, TI end, TE weight) override {
        if (this->vertexes.find(start) == this->vertexes.end() ||
            this->vertexes.find(end) == this->vertexes.end()) {
            return false; // Vertex doesn't exist
        }

        // Vertexes exist, so add edge
        std::shared_ptr<Vertex> start_vertex = this->vertexes[start];
        std::shared_ptr<Vertex> end_vertex = this->vertexes[end];

        // Check if edge already exists
        if (start_vertex->edges.find(end_vertex) != start_vertex->edges.end()) {
            return false; // Edge already exists
        }

        // Edge doesn't exist, so add it
        std::unique_ptr<Edge> new_edge_start = std::make_unique<Edge>();
        new_edge_start->vertexes[0] = start_vertex;
        new_edge_start->vertexes[1] = end_vertex;
        new_edge_start->weight = weight;

        std::unique_ptr<Edge> new_edge_end = std::make_unique<Edge>();
        new_edge_end->vertexes[0] = end_vertex;
        new_edge_end->vertexes[1] = start_vertex;
        new_edge_end->weight = weight;

        start_vertex->edges[end_vertex] = std::move(new_edge_start); // Add edge
        end_vertex->edges[start_vertex] = std::move(new_edge_end); // Add edge

        return true;
    }

    bool remove_vertex(TI key) override {
        if (this->vertexes.find(key) == this->vertexes.end()) {
            return false; // Vertex doesn't exist
        }

        // Vertex exists, so remove it
        std::shared_ptr<Vertex> vertex = this->vertexes[key];

        // Remove all edges that point to this vertex
        for (auto& [key, value] : vertex->edges) {
            key->edges.erase(vertex);
        }

        // Remove vertex
        this->vertexes.erase(key);

        return true;
    }

    bool remove_edge(TI start, TI end) override {
        if (this->vertexes.find(start) == this->vertexes.end() ||
            this->vertexes.find(end) == this->vertexes.end()) {
            return false; // Vertex doesn't exist
        }

        // Vertexes exist, so remove edge
        std::shared_ptr<Vertex> start_vertex = this->vertexes[start];
        std::shared_ptr<Vertex> end_vertex = this->vertexes[end];

        // Check if edge exists
        if (start_vertex->edges.find(end_vertex) == start_vertex->edges.end()) {
            return false; // Edge doesn't exist
        }

        // Edge exists, so remove it
        start_vertex->edges.erase(end_vertex);
        end_vertex->edges.erase(start_vertex);

        return true;
    }

    TE& operator() (TI start, TI end) override {
        if (this->vertexes.find(start) == this->vertexes.end() ||
            this->vertexes.find(end) == this->vertexes.end()) {
            throw std::out_of_range("Vertex doesn't exist");
        }

        // Vertexes exist, so return edge
        std::shared_ptr<Vertex> start_vertex = this->vertexes[start];
        std::shared_ptr<Vertex> end_vertex = this->vertexes[end];

        // Check if edge exists
        if (start_vertex->edges.find(end_vertex) == start_vertex->edges.end()) {
            throw std::out_of_range("Edge doesn't exist");
        }

        // Edge exists, so return it
        return start_vertex->edges[end_vertex]->weight;
    }

    operator bool() const override {
        return false; // Graph is undirected
    }

    float density() override {
        if (this->vertexes.empty()) {
            return 0.0f; // Graph is empty
        }

        // Graph isn't empty, so calculate density
        int vertex_count = this->vertexes.size();
        int edge_count = 0;

        for (auto& [key, value] : this->vertexes) {
            edge_count += value->edges.size();
        }

        return (float) edge_count / (vertex_count * (vertex_count - 1));
    }

    bool is_dense(float threshold = 0.5) override {
        return this->density() >= threshold;
    }

    bool empty() override {
        return this->vertexes.empty();
    }

    void clear() override {
        for (auto& [key, value] : this->vertexes) {
            value->edges.clear(); // Remove all edges
        }

        this->vertexes.clear(); // Remove all vertexes
    }

    void display() override {
        for (auto& [key, value] : this->vertexes) {
            std::cout << "Vertex " << key << " (data: " << value->value << "):\n";
            for (auto& [key, value] : value->edges) {
                std::cout << "\tEdge to vertex " << key->key << " (data: " << key->value << ") with weight " << value->weight << "\n";
            }
        }
    }
};
