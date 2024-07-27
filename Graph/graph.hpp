#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <array>

constexpr float threshold = 0.5; 

template<typename TK, typename TV, typename TE>
class Graph {
protected:
    struct Vertex;
    struct Edge;

    struct Edge {
        static_assert(std::is_arithmetic<TE>::value, "Weight must be an arithmetic type.");
        TE weight;
        std::array<Vertex*, 2> vertices;
    };

    struct Vertex {
        static_assert(std::is_arithmetic<TK>::value || std::is_same<TK, std::string>::value, "Key must be numeric or std::string.");
        TK key;
        TV value;
        std::unordered_map<Vertex*, Edge*> edges;
    };

    std::unordered_map<TK, Vertex*> vertices;

public:
    virtual bool insert_vertex(TK key, TV value) = 0;
    virtual bool insert_edge(TK start, TK end, TE weight) = 0;
    virtual bool remove_vertex(TK key) = 0;
    virtual bool remove_edge(TK start, TK end) = 0;

    virtual TE& operator() (TK start, TK end) = 0;
    virtual bool is_directed() const = 0;
    virtual float density() const = 0;
    virtual bool is_dense() const = 0;
    virtual bool empty() const = 0;
    virtual void clear() = 0;
    virtual void display() const = 0;
    virtual void display_vertex(TK id) const = 0;
    
    const std::unordered_map<TK, Vertex*>& get_vertices() const {
        return this->vertices;
    }

protected:
    void clear_edges(Vertex* vertex) {
        for (auto& pair : vertex->edges) {
            delete pair.second;
        }
        vertex->edges.clear();
    }
};

#endif // GRAPH_HPP
