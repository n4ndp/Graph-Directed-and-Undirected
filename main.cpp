#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Graph/dgraph.hpp"
#include "Graph/ugraph.hpp"
#include "include/nlohmann/json.hpp"

constexpr double toRadians(double degree) {
    return degree * M_PI / 180.0;
}

double haversine(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371.0;

    double lat1Rad = toRadians(lat1);
    double lon1Rad = toRadians(lon1);
    double lat2Rad = toRadians(lat2);
    double lon2Rad = toRadians(lon2);

    double dlat = lat2Rad - lat1Rad;
    double dlon = lon2Rad - lon1Rad;

    double a = std::sin(dlat / 2) * std::sin(dlat / 2) +
               std::cos(lat1Rad) * std::cos(lat2Rad) *
               std::sin(dlon / 2) * std::sin(dlon / 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    return R * c;
}

int main () {
    const std::string filename = "data/pe.json";

    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    nlohmann::json json_data;
    try {
        input_file >> json_data;
    } catch (nlohmann::json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return 1;
    }

    // build
    DirectedGraph<int, std::string, double> airports;

    for (const auto& item : json_data) {
        int airport_id = std::stoi(item["Airport ID"].get<std::string>());
        std::string airport_name = item["Name"];
        airports.insert_vertex(airport_id, airport_name);
    }

    for (const auto& item : json_data) {
        int source_id = std::stoi(item["Airport ID"].get<std::string>());
        double source_lat = std::stod(item["Latitude"].get<std::string>());
        double source_lon = std::stod(item["Longitude"].get<std::string>());

        for (const auto& dest_id_str : item["destinations"]) {
            int dest_id = std::stoi(dest_id_str.get<std::string>());

            auto dest_it = std::find_if(json_data.begin(), json_data.end(), [&dest_id](const nlohmann::json& el) { 
                return std::stoi(el["Airport ID"].get<std::string>()) == dest_id; 
            });

            if (dest_it != json_data.end()) {
                double dest_lat = std::stod((*dest_it)["Latitude"].get<std::string>());
                double dest_lon = std::stod((*dest_it)["Longitude"].get<std::string>());

                double distance = haversine(source_lat, source_lon, dest_lat, dest_lon);
                airports.insert_edge(source_id, dest_id, distance);
            }
        }
    }

    airports.display();

    return 0;
}
