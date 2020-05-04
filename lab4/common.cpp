#include <iostream>
#include <vector>
#include <math.h>
#include "common.h"

std::vector<double> fixed_step(int n, double a, double b) {
    std::vector<double> points;
    double h = (b - a) / n;
    for (int i = 0; i < n; i++) {
        points.push_back(a + i * h);
    }
    return points;
}

std::vector<double> chebyshev_nodes(int n, double a, double b) {
    std::vector<double> points;
    for (int k = 1; k <= n; k++) {
        points.push_back(0.5 * (a + b) + 0.5 * (b - a) * cos(((2.0 * k - 1) / (2 * n)) * M_PI));
    }
    return points;
}