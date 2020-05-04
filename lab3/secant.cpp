#include <iostream>
#include <functional>
#include <cmath>
#include <cfloat>

struct result {
    double x;
    int iteration_count;
};

typedef std::function<double(double)> func;

func f1 = [](double x) { return cos(x) * cosh(x) - 1; };
func f2 = [](double x) { return 1 / x - tan(x); };
func f3 = [](double x) { return pow(0.5, x) + exp(x) + 2 * cos(x) - 6; };

result secant(func f, double left, double right, int max_iter, double eps) {
    double x1 = right;
    double x2 = left;
    int iter = 0;
    double prev_val = f((right + left) / 2);

    while (iter < max_iter) {
        double x = (x2 * f(x1) - x1 * f(x2)) / (f(x1) - f(x2));
        if (std::abs(prev_val - f(x1)) < eps) {
            break;
        }

        prev_val = f(x1);
        x2 = x1;
        x1 = x;
        iter++;
    }

    return { .x = x1, .iteration_count = iter };
}

int main() {
    // auto res = secant(f2, 10e-7, M_PI / 2 - 10e-7, 100, 10e-15);
    // std::cout << res.x << std::endl;
    // std::cout << res.iteration_count << std::endl;
    double lol = 10e-33;
    std::cout << lol << std::endl;
    std::cout << DBL_MIN_EXP;

    return 0;
}