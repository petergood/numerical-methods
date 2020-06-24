#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

std::vector<std::complex<double>> dft(std::vector<double> X) {
    std::vector<std::complex<double>> res;
    int N = X.size();

    for (int k = 0; k < N; k++) {
        std::complex<double> s = 0;

        for (int n = 0; n < N; n++) {
            s += X[n] * std::complex<double>(cos(2 * M_PI * k * n / N), -sin(2 * M_PI * k * n / N));
        }

        res.push_back(s);
    }

    return res;
}

int main() {
    std::vector<double> X;
    int n;
    std::cin >> n;
    
    for (int i = 0; i < n; i++) {
        double x;
        std::cin >> x;
        X.push_back(x);
    }

    auto res = dft(X);

    for (auto x : res) {
        std::cout << std::abs(x) << std::endl;
    }

    std::cerr << "size: " << res.size() << std::endl;

    return 0;
}