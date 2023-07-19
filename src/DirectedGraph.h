#ifndef DirectedGraph_H
#define DirectedGraph_H

#include "graph.h"

template<typename TI, typename TV, typename TE>
class DirectedGraph : public Graph<TI, TV, TE> {
public:
    bool insertVertex(const TI& id, const TV& vertex) override;
    bool createEdge(const TI& id1, const TI& id2, const TE& weight) override;
    bool deleteVertex(const TI& id) override;
    bool deleteEdge(const TI& id1, const TI& id2) override;
    TE& operator()(const TI& id1, const TI& id2) override;
    float density() const override;
    bool isDense(float threshold = 0.5) const override;
    bool empty() const override;
    void clear() override;

    void display() const override;
    void displayVertex(const TI& id) const override;
    TV findById(const TI& id) override;
};

template<typename TI, typename TV, typename TE>
bool DirectedGraph<TI, TV, TE>::insertVertex(const TI& id, const TV& vertex) {
    if (this->vertexes.find(id) != this->vertexes.end()) {
        return false; // El vértice ya existe en el grafo
    }

    Vertex<TI, TV, TE>* newVertex = new Vertex<TI, TV, TE>{id, vertex};
    this->vertexes[id] = newVertex;
    return true;
}

template<typename TI, typename TV, typename TE>
bool DirectedGraph<TI, TV, TE>::createEdge(const TI& id1, const TI& id2, const TE& weight) {
    if (this->vertexes.find(id1) == this->vertexes.end() || this->vertexes.find(id2) == this->vertexes.end())
        return false; // Uno o ambos vértices no existen en el grafo

    // Buscar si la arista ya existe
    for (Edge<TI, TV, TE>* edge : this->vertexes[id1]->edges) {
        if (edge->vertexes[1]->id == id2) {
            // La arista ya existe, actualizar el peso
            edge->weight = weight;
            return true;
        }
    }

    // La arista no existe, crearla
    Vertex<TI, TV, TE>* vertex1 = this->vertexes[id1];
    Vertex<TI, TV, TE>* vertex2 = this->vertexes[id2];

    Edge<TI, TV, TE>* newEdge = new Edge<TI, TV, TE>{{vertex1, vertex2}, weight};
    vertex1->edges.push_back(newEdge);

    return true;
}

template<typename TI, typename TV, typename TE>
bool DirectedGraph<TI, TV, TE>::deleteVertex(const TI& id) {
    if (this->vertexes.find(id) == this->vertexes.end())
        return false; // El vértice no existe en el grafo

    Vertex<TI, TV, TE>* vertex = this->vertexes[id];
    
    // Eliminar las aristas que tienen al vértice como destino
    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it) {
        Vertex<TI, TV, TE>* v = it->second;
        v->edges.remove_if([vertex](Edge<TI, TV, TE>* edge) {
            return edge->vertexes[1] == vertex;
        });
    }

    // Eliminar las aristas que tienen al vértice como origen
    vertex->edges.clear();

    // Eliminar el vértice del grafo
    delete vertex;
    this->vertexes.erase(id);

    return true;
}

template<typename TI, typename TV, typename TE>
bool DirectedGraph<TI, TV, TE>::deleteEdge(const TI& id1, const TI& id2) {
    if (this->vertexes.find(id1) == this->vertexes.end() || this->vertexes.find(id2) == this->vertexes.end())
        return false; // Uno o ambos vértices no existen en el grafo

    Vertex<TI, TV, TE>* vertex1 = this->vertexes[id1];
    Vertex<TI, TV, TE>* vertex2 = this->vertexes[id2];

    // Buscar la arista en el sentido id1 -> id2
    Edge<TI, TV, TE>* edge1 = nullptr;
    for (Edge<TI, TV, TE>* edge : vertex1->edges) {
        if (edge->vertexes[1] == vertex2) {
            edge1 = edge;
            break;
        }
    }

    // Verificar si se encontró la arista
    if (edge1 == nullptr)
        return false; // La arista no existe en el grafo

    // Eliminar la arista y liberar la memoria
    vertex1->edges.remove(edge1);
    delete edge1;

    return true;
}

template<typename TI, typename TV, typename TE>
TE& DirectedGraph<TI, TV, TE>::operator()(const TI& id1, const TI& id2) {
    if (this->vertexes.find(id1) == this->vertexes.end() || this->vertexes.find(id2) == this->vertexes.end())
        throw std::out_of_range("One or both vertices do not exist in the graph.");

    Vertex<TI, TV, TE>* vertex1 = this->vertexes[id1];
    Vertex<TI, TV, TE>* vertex2 = this->vertexes[id2];

    // Buscar la arista desde el vértice id1 al vértice id2
    for (Edge<TI, TV, TE>* edge : vertex1->edges) {
        if (edge->vertexes[1] == vertex2)
            return edge->weight;
    }

    throw std::out_of_range("The edge does not exist between the given vertices.");
}

template<typename TI, typename TV, typename TE>
float DirectedGraph<TI, TV, TE>::density() const {
    // Calcular el número total de aristas posibles
    int vertexCount = this->vertexes.size();
    int maxEdges = vertexCount * (vertexCount - 1);

    // Contar el número de aristas existentes
    int edgeCount = 0;
    for (const auto& pair : this->vertexes) {
        const Vertex<TI, TV, TE>* vertex = pair.second;
        edgeCount += vertex->edges.size();
    }

    // Calcular la densidad
    if (maxEdges > 0)
        return static_cast<float>(edgeCount) / maxEdges;
    else
        return 0.0f;
}

template<typename TI, typename TV, typename TE>
bool DirectedGraph<TI, TV, TE>::isDense(float threshold) const {
    float graphDensity = density();
    return graphDensity >= threshold;
}

template<typename TI, typename TV, typename TE>
bool DirectedGraph<TI, TV, TE>::empty() const {
    return this->vertexes.empty();
}

template<typename TI, typename TV, typename TE>
void DirectedGraph<TI, TV, TE>::clear() {
    // Eliminar todos los vértices y aristas del grafo
    for (auto& pair : this->vertexes) {
        Vertex<TI, TV, TE>* vertex = pair.second;
        for (Edge<TI, TV, TE>* edge : vertex->edges) {
            delete edge;
        }
        delete vertex;
    }

    // Limpiar el contenedor de vértices
    this->vertexes.clear();
}

template<typename TI, typename TV, typename TE>
void DirectedGraph<TI, TV, TE>::display() const {
    for (const auto& pair : this->vertexes) {
        const Vertex<TI, TV, TE>* vertex = pair.second;
        std::cout << "Vertex ID: " << vertex->id << ", Data: " << vertex->data << std::endl;
        std::cout << "Outgoing Adjacent Vertices:" << std::endl;
        for (const Edge<TI, TV, TE>* edge : vertex->edges) {
            const Vertex<TI, TV, TE>* adjacentVertex = edge->vertexes[1];
            std::cout << "  - Vertex ID: " << adjacentVertex->id;
            std::cout << ", Data: " << adjacentVertex->data;
            std::cout << ", Weight: " << edge->weight << std::endl;
        }
        std::cout << std::endl;
    }
}

template<typename TI, typename TV, typename TE>
void DirectedGraph<TI, TV, TE>::displayVertex(const TI& id) const {
    if (this->vertexes.find(id) == this->vertexes.end()) {
        std::cout << "Vertex with ID " << id << " does not exist in the graph." << std::endl;
        return;
    }

    const Vertex<TI, TV, TE>* vertex = this->vertexes.at(id);
    std::cout << "Vertex ID: " << vertex->id << ", Data: " << vertex->data << std::endl;
    std::cout << "Outgoing Adjacent Vertices:" << std::endl;
    for (const Edge<TI, TV, TE>* edge : vertex->edges) {
        const Vertex<TI, TV, TE>* adjacentVertex = edge->vertexes[1];
        std::cout << "  - Vertex ID: " << adjacentVertex->id;
        std::cout << ", Data: " << adjacentVertex->data;
        std::cout << ", Weight: " << edge->weight << std::endl;
    }
    std::cout << std::endl;
}

template<typename TI, typename TV, typename TE>
TV DirectedGraph<TI, TV, TE>::findById(const TI& id) {
    if (this->vertexes.find(id) != this->vertexes.end()) {
        return this->vertexes[id]->data;
    }
    throw std::out_of_range("Vertex with the given ID does not exist.");
}

#endif
