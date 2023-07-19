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
    bool isConnected() const override; // StronglyConnected
    bool empty() const override;
    void clear() override;

    void display() const override;
    void displayVertex(const TI& id) const override;
    TV findById(const TI& id) override;
};

template<typename TI, typename TV, typename TE>
bool DirectedGraph<TI, TV, TE>::insertVertex(const TI& id, const TV& vertex) {
    if (vertexes.find(id) != vertexes.end()) {
        return false; // El vértice ya existe en el grafo
    }

    Vertex<TI, TV, TE>* newVertex = new Vertex<TI, TV, TE>{id, vertex};
    vertexes[id] = newVertex;
    return true;
}

template<typename TI, typename TV, typename TE>
bool DirectedGraph<TI, TV, TE>::createEdge(const TI& id1, const TI& id2, const TE& weight) {
    if (vertexes.find(id1) == vertexes.end() || vertexes.find(id2) == vertexes.end())
        return false; // Uno o ambos vértices no existen en el grafo

    // Buscar si la arista ya existe
    for (Edge<TV, TE>* edge : vertexes[id1]->edges) {
        if (edge->vertexes[1]->id == id2) {
            // La arista ya existe, actualizar el peso
            edge->weight = weight;
            return true;
        }
    }

    // La arista no existe, crearla
    Vertex<TI, TV, TE>* vertex1 = vertexes[id1];
    Vertex<TI, TV, TE>* vertex2 = vertexes[id2];

    Edge<TV, TE>* newEdge = new Edge<TV, TE>{{vertex1, vertex2}, weight};
    vertex1->edges.push_back(newEdge);

    return true;
}

template<typename TI, typename TV, typename TE>
bool DirectedGraph<TI, TV, TE>::deleteVertex(const TI& id) {
    if (vertexes.find(id) == vertexes.end())
        return false; // El vértice no existe en el grafo

    // Eliminar todas las aristas incidentes al vértice
    Vertex<TI, TV, TE>* vertex = vertexes[id];
    for (Edge<TV, TE>* edge : vertex->edges) {
        Vertex<TI, TV, TE>* adjacentVertex = edge->vertexes[1];
        for (auto it = adjacentVertex->edges.begin(); it != adjacentVertex->edges.end(); ++it) {
            if ((*it)->vertexes[1] == vertex) {
                delete *it;
                adjacentVertex->edges.erase(it);
                break;
            }
        }
    }

    // Eliminar el vértice y liberar la memoria
    delete vertex;
    vertexes.erase(id);

    return true;
}

template<typename TI, typename TV, typename TE>
bool DirectedGraph<TI, TV, TE>::deleteEdge(const TI& id1, const TI& id2) {
    if (vertexes.find(id1) == vertexes.end() || vertexes.find(id2) == vertexes.end())
        return false; // Uno o ambos vértices no existen en el grafo

    Vertex<TI, TV, TE>* vertex1 = vertexes[id1];
    Vertex<TI, TV, TE>* vertex2 = vertexes[id2];

    // Buscar la arista en el sentido id1 -> id2
    Edge<TV, TE>* edge1 = nullptr;
    for (Edge<TV, TE>* edge : vertex1->edges) {
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
    if (vertexes.find(id1) == vertexes.end() || vertexes.find(id2) == vertexes.end())
        throw std::out_of_range("One or both vertices do not exist in the graph.");

    Vertex<TI, TV, TE>* vertex1 = vertexes[id1];
    Vertex<TI, TV, TE>* vertex2 = vertexes[id2];

    // Buscar la arista desde el vértice id1 al vértice id2
    for (Edge<TV, TE>* edge : vertex1->edges) {
        if (edge->vertexes[1] == vertex2)
            return edge->weight;
    }

    throw std::out_of_range("The edge does not exist between the given vertices.");
}

template<typename TI, typename TV, typename TE>
float DirectedGraph<TI, TV, TE>::density() const {
    // Calcular el número total de aristas posibles
    int vertexCount = vertexes.size();
    int maxEdges = vertexCount * (vertexCount - 1);

    // Contar el número de aristas existentes
    int edgeCount = 0;
    for (const auto& pair : vertexes) {
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
    return vertexes.empty();
}


#endif
