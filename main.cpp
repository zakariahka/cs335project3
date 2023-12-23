#include "nearestneighbor.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <chrono>
#include <limits>
#include <algorithm>
#include <sstream>

int main() {
    std::string filename = "cu.txt";

    nearestNeighbor(filename);

    return 0;
}