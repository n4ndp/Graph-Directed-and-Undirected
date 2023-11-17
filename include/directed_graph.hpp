#include "graph.hpp"

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
        if (this->vertexes.find(start) == this->vertexes.end() || 
            this->vertexes.find(end) == this->vertexes.end()) {
            return false; // one or both vertexes don't exist
        }
        // vertexes exist, so add edge
        Vertex<TV, TE>* start_vertex = this->vertexes[start];

        // check if edge already exists
        if (start_vertex->edges.find(this->vertexes[end]) != start_vertex->edges.end()) {
            return false; // edge already exists
        }
        // edge doesn't exist, so add it
        Edge<TV, TE>* new_edge = new Edge<TV, TE>;
        new_edge->vertexes[0] = start_vertex;
        new_edge->vertexes[1] = this->vertexes[end];
        new_edge->weight = edge;
        start_vertex->edges[this->vertexes[end]] = new_edge;

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
        // graph isn't empty, so calculate density for directed graph
        float density = 0.0f;
        for (auto& vertex : this->vertexes) {
            density += vertex.second->edges.size();
        }
        density /= this->vertexes.size() * (this->vertexes.size() - 1);

        return density; // return density
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
            std::cout << vertex.first << ": ";
            for (auto& edge : vertex.second->edges) {
                std::cout << edge.first->data << " ";
            }
            std::cout << std::endl;
        }
    }
};
