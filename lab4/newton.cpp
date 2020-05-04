#include <iostream>
#include <functional>
#include <vector>
#include <math.h>
#include "common.h"

typedef std::function<double(double)> func;
func f1 = [](double x) { return sin(5 * x / M_PI) * exp(-1 * x / M_PI); };

double newton_function(int n, std::vector<double> points, func f, double x) {
    std::vector<std::vector<double>> table;

    for (int i = 0; i < n; i++) {
        table.push_back(std::vector<double>());
        table[i].push_back(f(points[i]));
        for (int j = 1; j < n; j++) {
            table[i].push_back(0);
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= i; j++) {
            table[i][j] = (table[i][j - 1] - table[i - 1][j - 1]) / (points[i] - points[i - j]);
        }
    }

    double y = 0;
    
    for (int i = 0; i < n; i++) {
        double a = table[i][i];

        for (int j = 0; j < i; j++) {
            a *= x - points[j];
        }

        y += a;
    }

    return y;
}

double err(func f, std::vector<double> points, int n, std::vector<double> test_points) {
    double e = 0;
    for (auto point : test_points) {
        e += std::abs(f(point) - newton_function(n, points, f, point));
    }
    return e;
}

int main() {
    int n;
    std::cin >> n;
    auto points = chebyshev_nodes(n, -10, 10);

    auto render_points = fixed_step(500, -10, 5);
    for (double point : render_points) {
        std::cout << point << "\t" << newton_function(n, points, f1, point) << std::endl;
    }

    std::cerr << "Error: " << err(f1, points, n, fixed_step(1000, -10, 10));

    return 0;
}