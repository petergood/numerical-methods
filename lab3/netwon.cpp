#include <iostream>
#include <functional>
#include <cmath>

struct result {
    double x;
    int iteration_count;
};

typedef std::function<double(double)> func;

func f1 = [](double x) { return cos(x) * cosh(x) - 1; };
func f1_deriv = [](double x) { return cos(x) * sinh(x) - sin(x) * cosh(x); };

func f2 = [](double x) { return 1 / x - tan(x); };
func f2_deriv = [](double x) { return - 1 / (x * x) - (1 + tan(x) * tan(x)); };

func f3 = [](double x) { return pow(0.5, x) + exp(x) + 2 * cos(x) - 6; };
func f3_deriv = [](double x) { return exp(x) - pow(0.5, x) * log(2) - 2 * sin(x); };

result newton(func f, func deriv, double left, double right, int max_iter, double eps) {
    double x = (left + right) / 2;
    double h = f(x) / deriv(x);
    int iter_count = 0;
    while (std::abs(h) >= eps && iter_count < max_iter) {
        h = f(x) / deriv(x);
        x = x - h;
        iter_count++;
    }

    result res;
    res.iteration_count = iter_count;
    res.x = x;
    return res;
} 

int main() {
    auto res = newton(f3, f3_deriv, 1, 3, 100, 10e-33);
    std::cout << res.x << std::endl;
    std::cout << res.iteration_count << std::endl;

    return 0;
}