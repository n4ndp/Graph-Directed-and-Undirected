#pragma once
#include <iostream>
#include <random>
#include <type_traits>

// function to generate random values for arithmetic types (int, float, double, etc.)
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
random_value() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> distrib(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    return distrib(gen);
}

// function to generate random values for std::string type
std::string random_value() {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, alphabet.size() - 1);
    int length = distrib(gen); // Longitud aleatoria para el string
    std::string result;
    for (int i = 0; i < length; ++i) {
        result += alphabet[distrib(gen)];
    }
    return result;
}
