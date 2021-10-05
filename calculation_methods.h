#ifndef SOLVER_H
#define SOLVER_H


#include <vector>
#include <utility>

#include "distant_matrix.h"


std::pair<std::vector<size_t>, double> 
brute_force(const DistantMatrix& matrix);

std::pair<std::vector<size_t>, double> 
nearest_neighbour(const DistantMatrix& matrix);


#endif
