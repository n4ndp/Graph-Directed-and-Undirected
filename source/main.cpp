#include <random>
#include "../include/undirected_graph.hpp"
#include "../include/directed_graph.hpp"

void test_for_dir() {
    DirectedGraph<int, int, int> graph;

    // Generación de valores aleatorios para los vértices
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> vertex_values(0, 100); // Rango de valores aleatorios

    for (int i = 0; i < 7; ++i) {
        int vertex_value = vertex_values(gen); // Generar valor aleatorio para el vértice
        graph.add_vertex(i, vertex_value);
    }

    // Añadir aristas al azar con valores aleatorios
    std::uniform_int_distribution<> edge_values(1, 10); // Rango de valores aleatorios para las aristas

    for (int i = 0; i < 3; ++i) {
        int from = std::uniform_int_distribution<>(0, 6)(gen); // Vértice de origen aleatorio
        int to = std::uniform_int_distribution<>(0, 6)(gen);   // Vértice de destino aleatorio
        int edge_value = edge_values(gen); // Valor aleatorio para la arista
        graph.add_edge(from, to, edge_value);
    }

    graph.display();
}

void test_for_undir() {
    UndirectedGraph<int, int, int> graph;

    // Generación de valores aleatorios para los vértices
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> vertex_values(0, 100); // Rango de valores aleatorios

    for (int i = 0; i < 7; ++i) {
        int vertex_value = vertex_values(gen); // Generar valor aleatorio para el vértice
        graph.add_vertex(i, vertex_value);
    }

    // Añadir aristas al azar con valores aleatorios
    std::uniform_int_distribution<> edge_values(1, 10); // Rango de valores aleatorios para las aristas

    for (int i = 0; i < 3; ++i) {
        int from = std::uniform_int_distribution<>(0, 6)(gen); // Vértice de origen aleatorio
        int to = std::uniform_int_distribution<>(0, 6)(gen);   // Vértice de destino aleatorio
        int edge_value = edge_values(gen); // Valor aleatorio para la arista
        graph.add_edge(from, to, edge_value);
    }

    graph.display();
}

int main(int argc, char const *argv[]) {
    test_for_undir();
    return 0;
}
