#ifndef DGRAPH_HPP
#define DGRAPH_HPP

#include "graph.hpp"

template<typename TK, typename TV, typename TE>
class DirectedGraph : public Graph<TK, TV, TE> {
public:
    bool insert_vertex(TK key, TV value) override {
        if (this->vertices.find(key) != this->vertices.end()) {
            return false;
        }

        this->vertices[key] = new typename Graph<TK, TV, TE>::Vertex{key, value};

        return true;
    }

    bool insert_edge(TK start, TK end, TE weight) override {
        auto it_start = this->vertices.find(start);
        auto it_end = this->vertices.find(end);
        if (it_start == this->vertices.end() || it_end == this->vertices.end()) {
            return false;
        }

        auto edge = new typename Graph<TK, TV, TE>::Edge{weight, {it_start->second, it_end->second}};
        it_start->second->edges[it_end->second] = edge;

        return true;
    }

    bool remove_vertex(TK key) override {
        auto it = this->vertices.find(key);
        if (it == this->vertices.end()) {
            return false;
        }

        for (auto& edge_pair : it->second->edges) {
            delete edge_pair.second;
        }
        it->second->edges.clear();

        for (auto& pair : this->vertices) {
            auto edge_it = pair.second->edges.find(it->second);
            if (edge_it != pair.second->edges.end()) {
                delete edge_it->second;
                pair.second->edges.erase(edge_it);
            }
        }

        delete it->second;
        this->vertices.erase(it);

        return true;
    }

    bool remove_edge(TK start, TK end) override {
        auto it_start = this->vertices.find(start);
        auto it_end = this->vertices.find(end);

        if (it_start == this->vertices.end() || it_end == this->vertices.end()) {
            return false;
        }

        auto edge_it = it_start->second->edges.find(it_end->second);
        if (edge_it == it_start->second->edges.end()) {
            return false;
        }

        delete edge_it->second;
        it_start->second->edges.erase(edge_it);

        return true;
    }

    TE& operator() (TK start, TK end) override {
        auto it_start = this->vertices.find(start);
        auto it_end = this->vertices.find(end);
        if (it_start == this->vertices.end() || it_end == this->vertices.end()) {
            throw std::out_of_range("One or both vertices not found");
        }

        auto edge_it = it_start->second->edges.find(it_end->second);
        if (edge_it == it_start->second->edges.end()) {
            throw std::out_of_range("Edge not found");
        }

        return edge_it->second->weight;
    }

    bool is_directed() const override {
        return true;
    }

    float density() const override {
        size_t num_vertices = this->vertices.size();
        size_t num_edges = 0;
        for (const auto& pair : this->vertices) {
            num_edges += pair.second->edges.size();
        }

        if (num_vertices == 0) return 0.0f;
        
        return static_cast<float>(num_edges) / (num_vertices * (num_vertices - 1));
    }

    bool is_dense() const override {
        return density() >= threshold;
    }

    bool empty() const override {
        return this->vertices.empty();
    }

    void clear() override {
        for (auto& pair : this->vertices) {
            this->clear_edges(pair.second);
            delete pair.second;
        }
        this->vertices.clear();
    }

    void display() const override {
        for (const auto& pair : this->vertices) {
            std::cout << "Vertex: " << pair.first << " -> " << pair.second->value << std::endl;
            for (const auto& edge_pair : pair.second->edges) {
                std::cout << "  Edge to " << edge_pair.first->key << " with weight " << edge_pair.second->weight << std::endl;
            }
        }
    }

    void display_vertex(TK id) const override {
        auto it = this->vertices.find(id);
        if (it == this->vertices.end()) {
            std::cout << "Vertex not found" << std::endl;
            return;
        }

        std::cout << "Vertex: " << it->first << " -> " << it->second->value << std::endl;
        for (const auto& edge_pair : it->second->edges) {
            std::cout << "  Edge to " << edge_pair.first->key << " with weight " << edge_pair.second->weight << std::endl;
        }
    }
};

#endif // DGRAPH_HPP
