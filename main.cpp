#include <iostream>
#include "src/DirectedGraph.h"
#include "src/UndirectedGraph.h"

void testDirectedGraph () {
    DirectedGraph<int, std::string, double> graph;

    // Insertar vértices
    graph.insertVertex(1, "Vertex 1");
    graph.insertVertex(2, "Vertex 2");
    graph.insertVertex(3, "Vertex 3");
    graph.insertVertex(4, "Vertex 4");
    graph.insertVertex(5, "Vertex 5");
    graph.insertVertex(6, "Vertex 6");

    // Crear aristas
    graph.createEdge(1, 2, 0.5);
    graph.createEdge(2, 3, 1.2);
    graph.createEdge(3, 4, 0.8);
    graph.createEdge(4, 5, 1.5);
    graph.createEdge(5, 6, 0.7);
    graph.createEdge(6, 1, 1.3);
    graph.createEdge(2, 4, 2.1);
    graph.createEdge(3, 5, 0.9);
    graph.createEdge(4, 6, 1.8);
    graph.createEdge(1, 3, 1.7);
    graph.createEdge(3, 6, 1.1);
    graph.createEdge(5, 1, 1.4);

    // Mostrar el grafo
    graph.display();

    // Acceder al peso de una arista
    double weight = graph(1, 2);
    std::cout << "Weight of edge (1, 2): " << weight << std::endl;

    // Verificar densidad
    float density = graph.density();
    std::cout << "Graph density: " << density << std::endl;

    // Verificar si el grafo es denso
    bool isDense = graph.isDense(0.5);
    std::cout << "Is the graph dense? " << (isDense ? "Yes" : "No") << std::endl;

    // Verificar si el grafo está vacío
    bool isEmpty = graph.empty();
    std::cout << "Is the graph empty? " << (isEmpty ? "Yes" : "No") << std::endl;

    // Eliminar una arista
    graph.deleteEdge(1, 2);

    // Mostrar el grafo después de eliminar la arista
    graph.display();

    // Eliminar un vértice
    graph.deleteVertex(3);

    // Mostrar el grafo después de eliminar el vértice
    graph.display();

    // Limpiar el grafo
    graph.clear();

    // Verificar si el grafo está vacío después de limpiarlo
    isEmpty = graph.empty();
    std::cout << "Is the graph empty after clearing? " << (isEmpty ? "Yes" : "No") << std::endl;
}

void testUndirectedGraph () {
    UndirectedGraph<int, std::string, double> graph;

    // Insertar vértices
    graph.insertVertex(1, "Vertex 1");
    graph.insertVertex(2, "Vertex 2");
    graph.insertVertex(3, "Vertex 3");
    graph.insertVertex(4, "Vertex 4");
    graph.insertVertex(5, "Vertex 5");
    graph.insertVertex(6, "Vertex 6");

    // Crear aristas
    graph.createEdge(1, 2, 0.5);
    graph.createEdge(2, 3, 1.2);
    graph.createEdge(3, 4, 0.8);
    graph.createEdge(4, 5, 1.5);
    graph.createEdge(5, 6, 0.7);
    graph.createEdge(6, 1, 1.3);
    graph.createEdge(2, 4, 2.1);
    graph.createEdge(3, 5, 0.9);
    graph.createEdge(4, 6, 1.8);
    graph.createEdge(1, 3, 1.7);
    graph.createEdge(3, 6, 1.1);
    graph.createEdge(5, 1, 1.4);

    // Mostrar el grafo
    graph.display();

    // Acceder al peso de una arista
    double weight = graph(1, 2);
    std::cout << "Weight of edge (1, 2): " << weight << std::endl;

    // Verificar densidad
    float density = graph.density();
    std::cout << "Graph density: " << density << std::endl;

    // Verificar si el grafo es denso
    bool isDense = graph.isDense(0.5);
    std::cout << "Is the graph dense? " << (isDense ? "Yes" : "No") << std::endl;

    // Verificar si el grafo está vacío
    bool isEmpty = graph.empty();
    std::cout << "Is the graph empty? " << (isEmpty ? "Yes" : "No") << std::endl;

    // Eliminar una arista
    graph.deleteEdge(1, 2);

    // Mostrar el grafo después de eliminar la arista
    graph.display();

    // Eliminar un vértice
    graph.deleteVertex(3);

    // Mostrar el grafo después de eliminar el vértice
    graph.display();

    // Limpiar el grafo
    graph.clear();

    // Verificar si el grafo está vacío después de limpiarlo
    isEmpty = graph.empty();
    std::cout << "Is the graph empty after clearing? " << (isEmpty ? "Yes" : "No") << std::endl;
}

int main() {
    testDirectedGraph();

    return 0;
}
