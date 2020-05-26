#include <iostream>
#include <functional>
#include <math.h>
#include <stdio.h>
#include <vector>

typedef std::function<double(double)> func;

func f1 = [](double x) { return 2 * std::pow(x, 3) + 3 * std::pow(x, 2) + 2 * x + 7; };
func f2 = [](double x) { return sin(x) * exp(x) + 10; };
func f3 = [](double x) { return sin(x) * x; };

double simpson_integrate(func f, double l, double r, int n) {
    double dx = (r - l) / n;
    double s = f(l) + f(r);

    double x = l + dx;
    for (int i = 1; i <= n - 1; i++) {
        s += 2 * f(x);
        x += dx;
    }

    x = l + dx / 2;
    for (int i = 1; i <= n; i++) {
        s += 4 * f(x);
        x += dx;
    }

    return (dx / 6.0) * s;
}

int main() {
    std::vector<int> n = { 1, 2, 4, 5, 10 };

    for (int i = 0; i < n.size(); i++) {
        std::cout << n[i] << " " << std::abs(3252850 - simpson_integrate(f1, 0, 50, n[i])) << std::endl;
    }

    return 0;
}