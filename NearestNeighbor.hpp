// NearestNeighbor.hpp
#ifndef NEAREST_NEIGHBOR_HPP
#define NEAREST_NEIGHBOR_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cmath>
#include <limits>
#include <algorithm>
#include <sstream>

class NODE
{
public:
    NODE(int id, double x, double y) : id_(id), x_(x), y_(y) {}

    int getId() const
    {
        return id_;
    }
    double getX() const
    {
        return x_;
    }
    double getY() const
    {
        return y_;
    }

    // calculating Euclidean distance between two nodes
    static double distance(const NODE &a, const NODE &b)
    {
        return std::hypot(a.x_ - b.x_, a.y_ - b.y_);
    }

private:
    int id_;
    double x_;
    double y_;
};

// Function to read nodes from a file and return a vector of NODEs
std::vector<NODE> read(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return {};
    }

    std::vector<NODE> nodes;
    std::string line;
    int id;
    double x, y;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        if (iss >> id >> x >> y)
        {
            nodes.emplace_back(id, x, y);
        }
    }

    return nodes;
}

// Function to perform the nearest neighbor algorithm on a set of nodes
void nearestNeighbor(const std::string &filename)
{
    auto nodes = read(filename);
    if (nodes.empty())
    {
        return;
    }

    std::vector<bool> seen(nodes.size(), false);
    std::vector<int> path;
    double tot = 0.0;

    auto current = nodes.begin();
    path.push_back(current->getId());
    seen[current - nodes.begin()] = true;

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 1; i < nodes.size(); ++i)
    {
        auto nearest = nodes.end();
        double minDistance = std::numeric_limits<double>::max();

        // Find the nearest unvisited node
        for (auto it = nodes.begin(); it != nodes.end(); ++it)
        {
            if (!seen[it - nodes.begin()])
            {
                double distance = NODE::distance(*current, *it);
                if (distance < minDistance)
                {
                    nearest = it;
                    minDistance = distance;
                }
            }
        }

        // Mark the nearest node as visited and update the total distance
        seen[nearest - nodes.begin()] = true;
        tot += minDistance;
        path.push_back(nearest->getId());
        current = nearest;
    }

    // Complete the path by adding the distance to the starting node
    tot += NODE::distance(*current, nodes.front());
    path.push_back(nodes.front().getId());

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Output the path, total distance, and execution time
    for (int id : path)
    {
        std::cout << id << " ";
    }
    std::cout << "\nTotal Distance: " << tot << "\nTime in ms: " << duration.count() << std::endl;
}

// Total Distance: 1.03496e+06
// Time in ms: 5924

#endif 
// NEAREST_NEIGHBOR_HPP