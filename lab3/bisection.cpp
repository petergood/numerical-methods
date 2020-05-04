#include <iostream>
#include <functional>
#include <cmath>

struct result {
    double x;
    int iteration_count;
};

typedef std::function<double(double)> func;

func f1 = [](double x) { return cos(x) * cosh(x) - 1; };
func f2 = [](double x) { return 1 / x - tan(x); };
func f3 = [](double x) { return pow(0.5, x) + exp(x) + 2 * cos(x) - 6; };

result bisection(func f, double left, double right, double eps) {
    if (f(left) * f(right) > 0) {
        throw std::runtime_error("Incorrect boundary values");
    }

    int iter_count = 0;

    while (std::abs(left - right) > eps) {
        double mid = (left + right) / 2;
        
        if (f(left) * f(mid) < 0) {
            right = mid;
        } else {
            left = mid;
        }

        iter_count++;
    } 

    result res;
    res.iteration_count = iter_count;
    res.x = left;
    return res;
}

int main() {
    auto res = bisection(f2, 0, M_PI / 2, 10e-7);

    std::cout << res.x << std::endl;
    std::cout << res.iteration_count << std::endl;

    return 0;
}