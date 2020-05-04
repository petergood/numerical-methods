#include <iostream>
#include <functional>
#include <vector>
#include <math.h>
#include "common.h"

typedef std::function<double(double)> func;
func f1 = [](double x) { return sin(5 * x / M_PI) * exp(-1 * x / M_PI); };

double lagrange_function(func f, std::vector<double> points, int n, double x) {
    double y = 0;

    for (int i = 0; i < n; i++) {
        double a = f(points[i]);
        
        for (int j = 0; j < n; j++) {
            if (i != j) {
                a *= (x - points[j]) / (points[i] - points[j]);
            }
        }

        y += a;
    }

    return y;
}

double err(func f, std::vector<double> points, int n, std::vector<double> test_points) {
    double e = 0;
    for (auto point : test_points) {
        e += std::abs(f(point) - lagrange_function(f, points, n, point));
    }
    return e;
} 

int main() {
    int n;
    std::cin >> n;
    auto points = chebyshev_nodes(n, -10, 10);
    auto render_points = fixed_step(100, -10, 5);

    for (auto point : render_points) {
        std::cout << point << "\t" << lagrange_function(f1, points, n, point) << std::endl;
    }

    std::cerr << "Error: " << err(f1, points, n, fixed_step(1000, -10, 10));

    return 0;
}