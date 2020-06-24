#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

typedef std::vector<std::complex<double>> comp_vec;

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

std::vector<std::complex<double>> fft(std::vector<double> X) {
    if (X.size() % 2 != 0) {
        throw "Size of X must be a power of 2";
    } else if (X.size() <= 32) {
        return dft(X);
    } else {
        std::vector<double> even, odd;
        int N = X.size();

        for (int i = 0; i < N; i++) {
            if (i % 2 == 0) {
                even.push_back(X[i]);
            } else {
                odd.push_back(X[i]);
            }
        }

        auto X_even = fft(even);
        auto X_odd = fft(odd);
        comp_vec res(N);

        for (int i = 0; i < N / 2; i++) {
            std::complex<double> factor = std::complex<double>(cos(-2 * M_PI * i / N), sin(-2 * M_PI * i / N)) * X_odd[i];
            res[i] = X_even[i] + factor;
            res[i + N / 2] = X_even[i] - factor;
        }

        return res;
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<double> x;

    for (int i = 0; i < n; i++) {
        int a;
        std::cin >> a;
        x.push_back(a);
    }

    auto res = fft(x);

    for (auto a : res) {
        std::cout << std::abs(a) << std::endl;
    }

    return 0;
}