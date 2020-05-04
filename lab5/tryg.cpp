#include <iostream>
#include <vector>
#include <functional>
#include <math.h>

std::vector<double> fixed_step(int n, double a, double b) {
    std::vector<double> points;
    double h = (b - a) / n;
    for (int i = 0; i < n; i++) {
        points.push_back(a + i * h);
    }
    return points;
}

typedef std::function<double(double)> func;
typedef std::pair<std::vector<double>, std::vector<double>> params;

func f1 = [](double x) { return exp(2 * cos(2 * x)); };
func f2 = [](double x) { return sin(3 * x) * exp(cos(2 * x)); };

params polynominal_params(int n, int L, func f) {
    params params;
    params.first = std::vector<double>();
    params.second = std::vector<double>();

    for (int j = 0; j < n; j++) {
        double sa = 0, sb = 0;

        for (int i = 0; i < 2 * L; i++) {
            double x = M_PI * i / L;
            sa += f(x) * cos(x * j);
        }

        for (int i = 0; i < 2 * L; i++) {
            double x = M_PI * i / L;
            sb += f(x) * sin(x * j);
        }

        params.first.push_back(sa / L);
        params.second.push_back(sb / L);
    }

    return params;
}

double tryg_polynomial(int n, params params, double x) {
    double s = 0.5 * params.first[0];
    for (int j = 1; j < n; j++) {
        s += params.first[j] * cos(j * x) + params.second[j] * sin(j * x);
    }

    return s;
}

double err(int n, int L, params params, func f) {
    double s = 0;
    for (int i = 0; i < 2 * L; i++) {
        double x = M_PI * i / L;
        s += pow(f(x) - tryg_polynomial(n, params, x), 2);
    }
    return s;
}

int main() {
    int n, L;
    std::cin >> n >> L;
    params params = polynominal_params(n, L, f2);

    auto render_points = fixed_step(100, -5, 5);

    for (auto point : render_points) {
        std::cout << point << "\t" << tryg_polynomial(n, params, point) << std::endl;
    }

    std::cerr << "Error: " << err(n, L, params, f2) << std::endl;

    return 0;
}