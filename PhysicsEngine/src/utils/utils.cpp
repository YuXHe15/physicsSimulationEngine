#include "utils.hpp"
#include "PhysicsObject.hpp"
#include <random>

char generateRandomLetter() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> distr(97, 122);
    return static_cast<char>(distr(gen));
}

std::string generateRandomName(int length) {
    std::string name;
    for (int i = 0; i < length; i++) {
        name += generateRandomLetter();
    }
    return name;
};

bool fequal(float a, float b, float tolerance) {
    return std::fabs(a - b) < tolerance;
};

