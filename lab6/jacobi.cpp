#include <iostream>
#include <vector>

double err(int n, std::vector<double> x, std::vector<double> sol) {
    double e = 0;

    for (int i = 0; i < n; i++) {
        e += std::abs(x[i] - sol[i]);
    }

    return e / n;
}

std::vector<double> jacobi(int n, int iter_count, std::vector<std::vector<double>> a, std::vector<double> b, std::vector<double> sol) {
    std::vector<double> x(n, 0);

    for (int k = 0; k < iter_count; k++) {
        std::vector<double> x_tmp(n, 0);

        for (int i = 0; i < n; i++) {
            double s = 0;
            for (int j = 0; j < n; j++) {
                if (j != i) s += a[i][j] * x[j];
            }

            x_tmp[i] = (1.0 / a[i][i]) * (b[i] - s); 
        }

        x = x_tmp;
        std::cout << k << " " << err(n, x, sol) << std::endl;
    }

    return x;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<double>> a;
    std::vector<double> b(n, 0);
    for (int i = 0; i < n; i++) {
        a.push_back(std::vector<double>(n, 0));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }

    std::vector<double> sol(n, 0);
    for (int i = 0; i < n; i++) {
        std::cin >> sol[i];
    }

    auto res = jacobi(n, 30, a, b, sol);
    for (double x : res) {
        std::cerr << x << " ";
    }
    std::cerr << std::endl;

    return 0;
}