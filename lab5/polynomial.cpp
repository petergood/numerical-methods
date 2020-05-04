#include <iostream>
#include <functional>
#include <vector>
#include <math.h>

typedef std::function<double(double)> func;

func f1 = [](double x) { return sin(5 * x / M_PI) * exp(-1 * x / M_PI); };
func f2 = [](double x) { return x * x - 4 * cos(x * M_PI / 2); };

std::vector<double> chebyshev_nodes(int n, double a, double b) {
    std::vector<double> points;
    for (int k = 1; k <= n; k++) {
        points.push_back(0.5 * (a + b) + 0.5 * (b - a) * cos(((2.0 * k - 1) / (2 * n)) * M_PI));
    }
    return points;
}

std::vector<double> fixed_step(int n, double a, double b) {
    std::vector<double> points;
    double h = (b - a) / n;
    for (int i = 0; i < n; i++) {
        points.push_back(a + i * h);
    }
    return points;
}

std::vector<std::vector<double>> get_parameter_matrix(int n, int m, std::vector<double> points, func f) {
    std::vector<std::vector<double>> mat;

    for (int i = 0; i < m; i++) {
        mat.push_back(std::vector<double>());
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                mat[i].push_back(n + 1);
            } else {
                double s = 0;
                for (double point : points) {
                    s += pow(point, j + i);
                }
                mat[i].push_back(s);
            }
        }

        double s = 0;
        for (int j = 0; j < n; j++) {
            s += f(points[j]) * pow(points[j], i);
        }
        mat[i].push_back(s);
    }

    return mat;
}

std::vector<double> polynomial_parameters(int n, int m, std::vector<double> points, func f) {
    auto mat = get_parameter_matrix(n, m, points, f);

    for (int k = 0; k < m; k++) {
        int mx = k;
        for (int i = k; i < m; i++) {
            if (abs(mat[i][k]) > abs(mat[mx][k])) {
                mx = i;
            }
        }

        for (int i = 0; i < m + 1; i++) {
            double b = mat[mx][i];
            mat[mx][i] = mat[k][i];
            mat[k][i] = b;
        }

        for (int i = k + 1; i < m; i++) {
            double f = mat[i][k] / mat[k][k];

            for (int j = k + 1; j < m + 1; j++) {
                mat[i][j] -= mat[k][j] * f;
            }

            mat[i][k] = 0;
        }
    }

    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < m + 1; j++) {
    //         printf("%20f", mat[i][j]);
    //     }
    //     printf("\n");
    // }

    std::vector<double> a(m, 0);

    for (int k = m - 1; k >= 0; k--) {
        double s = 0;
        for (int i = k + 1; i < m; i++) {
            s += mat[k][i] * a[i];
        }
        a[k] = (mat[k][m] - s) / mat[k][k];
    }

    return a;
}

double polynomial(int m, std::vector<double> a, double x) {
    double res = 0;
    for (int i = 0; i < m; i++) {
        res += a[i] * pow(x, i);
    }
    return res;
}

double err(int m, std::vector<double> a, std::vector<double> points, func f) {
    double s = 0;
    
    for (double point : points) {
        s += pow(f(point) - polynomial(m, a, point), 2);
    }

    return s;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    auto points = fixed_step(n, -10, 5);
    auto a = polynomial_parameters(n, m, points, f2);

    auto render_points = fixed_step(1000, -10, 5);

    for (double point : render_points) {
        std::cout << point << "\t" << polynomial(m, a, point) << std::endl;
    }

    std::cerr << "Error: " << err(m, a, points, f2) << std::endl;

    return 0;
}