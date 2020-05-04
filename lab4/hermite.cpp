#include <iostream>
#include <functional>
#include <vector>
#include <math.h>
#include "common.h"

typedef std::function<double(double)> func;

func f1 = [](double x) { return sin(5 * x / M_PI) * exp(-1 * x / M_PI); };
func f1_deriv = [](double x) { return (exp(-1 * x / M_PI) * (5 * cos(5 * x / M_PI) - sin(5 * x / M_PI))) / M_PI; };

double hermite_function(int n, func f, func f_deriv, std::vector<double> points, double x) {
    std::vector<std::vector<double>> table;
    std::vector<double> z;

    for (int i = 0; i < n; i++) {
        std::vector<double> row;
        row.push_back(f(points[i]));

        for (int j = 1; j < 2 * n; j++) {
            row.push_back(0);
        }

        table.push_back(row);
        table.push_back(std::vector<double>(row));
    
        z.push_back(points[i]);
        z.push_back(points[i]);
    }

    for (int i = 1; i < 2 * n; i++) {
        for (int j = 1; j <= i; j++) {
            if (j == 1 && i % 2 == 1) {
                table[i][j] = f_deriv(z[i]);
            } else {
                table[i][j] = (table[i][j - 1] - table[i - 1][j - 1]) / (z[i] - z[i - j]);
            }
        }
    }

    double res = 0;

    for (int k = 0; k < 2 * n; k++) {
        double a = table[k][k];

        for (int i = 0; i < k; i++) {
            a *= x - z[i];
        }

        res += a;
    }

    return res;
}

double err(func f, func f_deriv, std::vector<double> points, int n, std::vector<double> test_points) {
    double e = 0;
    for (auto point : test_points) {
        e += std::abs(f(point) - hermite_function(n, f, f_deriv, points, point));
    }
    return e;
}

int main() {
    int n;
    std::cin >> n;
    auto points = chebyshev_nodes(n, -10, 10);
    auto render_points = fixed_step(100, -10, 5);

    for (auto point : render_points) {
        std::cout << point << "\t" << hermite_function(n, f1, f1_deriv, points, point) << std::endl;
    }

    std::cerr << "Error: " << err(f1, f1_deriv, points, n, fixed_step(1000, -10, 10));

    return 0;
}