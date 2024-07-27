#include <iostream>
#include <cassert>
#include <string>
#include <random>
#include <vector>
#include <algorithm>
#include "dgraph.hpp"
#include "ugraph.hpp"

// Function to generate random float numbers
float random_float(float min, float max) {
    static std::default_random_engine e;
    static std::uniform_real_distribution<float> dis(min, max);
    return dis(e);
}

// Function to generate random integer numbers
int random_int(int min, int max) {
    static std::default_random_engine e;
    static std::uniform_int_distribution<int> dis(min, max);
    return dis(e);
}

void test_directed_graph() {
    DirectedGraph<int, std::string, float> dgraph;

    std::vector<int> vertices;

    // Insert vertices
    for (int i = 1; i <= 10; ++i) {
        assert(dgraph.insert_vertex(i, "Vertex" + std::to_string(i)) && "Failed to insert vertex");
        vertices.push_back(i);
    }

    // Insert edges
    for (int i = 0; i < vertices.size(); ++i) {
        for (int j = i + 1; j < vertices.size(); ++j) {
            assert(dgraph.insert_edge(vertices[i], vertices[j], random_float(1.0f, 10.0f)) && "Failed to insert edge");
        }
    }

    // Verify vertex insertion
    for (int i = 0; i < vertices.size(); ++i) {
        for (int j = i + 1; j < vertices.size(); ++j) {
            float weight = dgraph(vertices[i], vertices[j]);
            assert(weight >= 1.0f && weight <= 10.0f && "Edge weight out of expected range");
        }
    }

    // Randomly remove some edges
    for (int k = 0; k < 5; ++k) {
        int i = random_int(0, vertices.size() - 1);
        int j = random_int(0, vertices.size() - 1);
        while (i == j) j = random_int(0, vertices.size() - 1);
        dgraph.remove_edge(vertices[i], vertices[j]);
    }

    // Randomly remove some vertices
    std::random_shuffle(vertices.begin(), vertices.end());
    for (int i = 0; i < 5; ++i) {
        dgraph.remove_vertex(vertices.back());
        vertices.pop_back();
    }

    dgraph.display();
    std::cout << "Directed graph tests passed!" << std::endl;
}

void test_undirected_graph() {
    UndirectedGraph<int, std::string, float> ugraph;

    std::vector<int> vertices;

    // Insert vertices
    for (int i = 1; i <= 10; ++i) {
        assert(ugraph.insert_vertex(i, "Vertex" + std::to_string(i)) && "Failed to insert vertex");
        vertices.push_back(i);
    }

    // Insert edges
    for (int i = 0; i < vertices.size(); ++i) {
        for (int j = i + 1; j < vertices.size(); ++j) {
            assert(ugraph.insert_edge(vertices[i], vertices[j], random_float(1.0f, 10.0f)) && "Failed to insert edge");
        }
    }

    // Verify vertex insertion
    for (int i = 0; i < vertices.size(); ++i) {
        for (int j = i + 1; j < vertices.size(); ++j) {
            float weight = ugraph(vertices[i], vertices[j]);
            assert(weight >= 1.0f && weight <= 10.0f && "Edge weight out of expected range");
            weight = ugraph(vertices[j], vertices[i]);
            assert(weight >= 1.0f && weight <= 10.0f && "Edge weight out of expected range");
        }
    }

    // Randomly remove some edges
    for (int k = 0; k < 5; ++k) {
        int i = random_int(0, vertices.size() - 1);
        int j = random_int(0, vertices.size() - 1);
        while (i == j) j = random_int(0, vertices.size() - 1);
        ugraph.remove_edge(vertices[i], vertices[j]);
    }

    // Randomly remove some vertices
    std::random_shuffle(vertices.begin(), vertices.end());
    for (int i = 0; i < 5; ++i) {
        ugraph.remove_vertex(vertices.back());
        vertices.pop_back();
    }

    ugraph.display();
    std::cout << "Undirected graph tests passed!" << std::endl;
}

int main() {
    test_directed_graph();
    test_undirected_graph();
    return 0;
}
