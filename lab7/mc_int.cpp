#include <iostream>
#include <functional>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <time.h>

typedef std::function<double(double)> func;

func f1 = [](double x) { return 2 * std::pow(x, 3) + 3 * std::pow(x, 2) + 2 * x + 7; };
func f2 = [](double x) { return sin(x) * exp(x) + 10; };
func f3 = [](double x) { return sin(x) * x; };

double mc_integrate(func f, double l, double r, int n) {
    srand(time(NULL));
    double s = 0;
    
    for (int i = 0; i < n; i++) {
        double x = l + static_cast<double>(rand()) / (static_cast<float>(RAND_MAX / (r - l)));
        s += f(x);
    }

    return (r - l) * s / n;
}

int main() {
    std::vector<int> n = { 2, 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000 };

    for (int i = 0; i < n.size(); i++) {
        std::cout << n[i] << " " << std::abs(3252850 - mc_integrate(f1, 0, 50, n[i])) << std::endl;
    }

    return 0;
}