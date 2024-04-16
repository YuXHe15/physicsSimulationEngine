#ifndef UTILS_HPP
#define UTILS_HPP
#include <string>
#include <cmath>
#include <vector>

char generateRandomLetter();

std::string generateRandomName(int length);

bool fequal(float a, float b, float tolerance = 1e-5);

#endif