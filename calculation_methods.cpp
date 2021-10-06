#include "calculation_methods.h"

#include <iostream>
#include <algorithm>
#include <numeric>


double _tour_len(const std::vector<size_t>& vertices, 
                 const DistantMatrix& matrix);
size_t _factorial(size_t num);


std::pair<std::vector<size_t>, double> 
brute_force(const DistantMatrix& _matrix) 
{
    size_t size = _matrix.get_size();

    std::vector<size_t> cur_tour(size);
    std::vector<size_t> min_tour(size);

    for (size_t i = 0; i < size; i++)
        cur_tour[i] = i;
    min_tour = cur_tour;

    double cur_path = _tour_len(cur_tour, _matrix);
    double min_path = cur_path;

    size_t count = _factorial(size - 1) / 2;
    
    for (size_t i = 1; i < count; i++) 
    {
        // Rearranging the vertices in lexicographic order
        std::next_permutation(cur_tour.begin() + 1, cur_tour.end());
        cur_path = _tour_len(cur_tour, _matrix);

        if (cur_path < min_path) 
        {
            min_tour = cur_tour;
            min_path = cur_path;
        }
    }

    return std::pair<std::vector<size_t>, double>(min_tour, min_path);
}

std::pair<std::vector<size_t>, double>
nearest_neighbour(const DistantMatrix& _matrix) 
{
    size_t size = _matrix.get_size();
    std::vector<size_t> min_tour(size);

    // initialize min_tour to default tour: 1 -> 2 -> ... -> size - 1
    for (size_t i = 0; i < size; i++)
        min_tour[i] = i;

    // find the nearest neighbour for the vertex min_tour[i] and swap them
    for (size_t i = 0; i < size - 1; i++) 
    {
        size_t next_vertex = i + 1;
        double min_dist = _matrix.get_distant(min_tour[i], 
            min_tour[next_vertex]);

        for (size_t j = i + 2; j < size; j++) 
        {
            double cur_dist = _matrix.get_distant(min_tour[i], min_tour[j]);

            if (cur_dist < min_dist) 
            {
                min_dist = cur_dist;
                next_vertex = j;
            }
        }

        std::swap<size_t>(min_tour[i + 1], min_tour[next_vertex]);
    }

    double min_path = _tour_len(min_tour, _matrix);

    return std::pair<std::vector<size_t>, double>(min_tour, min_path);
}

double _tour_len(const std::vector<size_t>& _vertices,
                 const DistantMatrix& _matrix) 
{
    double path = 0;
    size_t count = _vertices.size();

    for (size_t i = 0; i < count; i++) 
    {
        // distant between last and first vertices
        if (i == count - 1)
            path += _matrix.get_distant(_vertices[i], _vertices[0]);
        // distant between current and next vertices
        else
            path += _matrix.get_distant(_vertices[i], _vertices[i + 1]);
    }

    return path;
}

size_t _factorial(size_t num) 
{
    size_t result = 1;

    for (size_t i = 2; i <= num; i++)
        result *= i;
    
    return result;
}
