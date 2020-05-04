#ifndef COMMON_H
#define COMMON_H

#include <vector>

std::vector<double> fixed_step(int n, double a, double b);
std::vector<double> chebyshev_nodes(int n, double a, double b);

#endif