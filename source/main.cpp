#include <random>
#include <fstream>
#include "../include/Graph/undirected_graph.hpp"
#include "../include/Graph/directed_graph.hpp"
#include "../include/json.hpp"

// Calculate the distance between two points with latitude and longitude
float distance(float lat1, float lon1, float lat2, float lon2) {
    float R = 6371e3; // metres
    float phi1 = lat1 * M_PI / 180; // φ, λ in radians
    float phi2 = lat2 * M_PI / 180;
    float delta_phi = (lat2 - lat1) * M_PI / 180;
    float delta_lambda = (lon2 - lon1) * M_PI / 180;

    float a = sin(delta_phi / 2) * sin(delta_phi / 2) +
              cos(phi1) * cos(phi2) *
              sin(delta_lambda / 2) * sin(delta_lambda / 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));

    float d = R * c; // in metres
    return d;
}

int main(int argc, char const *argv[]) {
    std::string file_path = "../data/pe.json";
    std::string air_code = "2789";

    std::ifstream input_file(file_path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open file: " << file_path << std::endl;
        return 1;
    }

    nlohmann::json json_data;
    try {
        input_file >> json_data;
    } catch (nlohmann::json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return 1;
    }

    UndirectedGraph<std::string, std::string, float> graph;

    for (auto &airport : json_data) {
        std::string id1 = airport["Airport ID"];
        std::string name1 = airport["Name"];
        std::string latitude1 = airport["Latitude"];
        std::string longitude1 = airport["Longitude"];

        graph.insert_vertex(id1, name1);
        for (const auto& destination : airport["destinations"]) {
            for (const auto&airport2 : json_data) {
                if (airport2["Airport ID"] == destination) {
                    
                    std::string id2 = airport2["Airport ID"];
                    std::string latitude2 = airport2["Latitude"];
                    std::string longitude2 = airport2["Longitude"];
                    
                    float lat1 = std::stof(latitude1);
                    float lon1 = std::stof(longitude1);
                    float lat2 = std::stof(latitude2);
                    float lon2 = std::stof(longitude2);

                    float dist = distance(lat1, lon1, lat2, lon2);
                    graph.insert_edge(id1, id2, dist);
                }
            }
        }
    }

    std::cout << "Graph: " << std::endl;
    graph.display();

    return 0;
}
