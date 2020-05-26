#include <iostream>
#include <functional>
#include <math.h>
#include <stdio.h>
#include <vector>

typedef std::function<double(double)> func;

func f1 = [](double x) { return 2 * std::pow(x, 3) + 3 * std::pow(x, 2) + 2 * x + 7; };
func f2 = [](double x) { return sin(x) * exp(x) + 10; };
func f3 = [](double x) { return sin(x) * x; };

double rect_integrate(func f, double l, double r, int n) {
    double dx = (r - l) / n;
    double s = 0;
    double x = l;

    for (int i = 0; i < n; i++) {
        // printf("set arrow nohead from %f,0 to %f,0\n", x, x + dx);
        // printf("set arrow nohead from %f,0 to %f,%f\n", x, x, f(x));
        // printf("set arrow nohead from %f,0 to %f,%f\n", x + dx, x + dx, f(x + dx));
        // printf("set arrow nohead from %f,%f to %f,%f\n", x, f(x), x + dx, f(x + dx));
        s += 0.5 * (f(x) + f(x + dx)) * dx;
        x += dx;
    }

    return s;
}

int main() {
    // std::cout << "set terminal png size 580,800" << std::endl;
    // std::cout << "set output \"plot6.png\"" << std::endl;
    // std::cout << "set multiplot layout 3, 2 title \"f3\";" << std::endl;

    std::vector<int> n = { 5, 20, 30, 50, 100, 200, 500 };

    for (int i = 0; i < n.size(); i++) {
        // std::cout << "set title \"n = " << n[i] << "\"" << std::endl;
        // double res = rect_integrate(f3, -3, 3, n[i]);
        // std::cout << "set label at graph 0.25,0.8 \"S=" << res << "\"" << std::endl;
        // std::cout << "plot [-3:3] sin(x) * x title \"f3\"" << std::endl << std::endl;
        // std::cout << "unset label" << std::endl;
        // std::cout << "unset arrow" << std::endl;

        std::cout << n[i] << " " << std::abs(6.2222 - rect_integrate(f3, -3, 3, n[i])) << std::endl;
    }

    return 0;
}