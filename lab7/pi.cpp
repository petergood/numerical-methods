#include <iostream>
#include <time.h>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <string>

double monte_carlo_pi(int a, int n) {
    srand(time(NULL));
    std::string fn = "points_" + std::to_string(n);
    FILE* f = fopen(fn.c_str(), "w");

    int inside = 0;
    for (int i = 0; i < n; i++) {
        double x = rand() % a;
        double y = rand() % a;
        bool in = false;

        if (std::pow(x - a / 2.0, 2) + std::pow(y - a / 2.0, 2) < std::pow(a / 2.0, 2)) {
            inside++;
            in = true;
        }

        fprintf(f, "%f %f %f\n", x, y, in ? 0.0 : 1.0);
    }

    fclose(f);
    return 4.0 * inside / n;
}

int main() {
    std::cout << "set terminal png size 580,800" << std::endl;
    std::cout << "set output \"plot_pi.png\"" << std::endl;
    std::cout << "set multiplot layout 3, 2 title \"Monte Carlo Pi (a = 100000)\";" << std::endl;
    std::cout << "set cbrange [0:1]\n" << std::endl;
    std::cout << "set palette defined ( 0.5 \"#34eb5c\", 1 \"#eb4034\")" << std::endl;
    std::cout << "unset colorbox\n" << std::endl;
    std::cout << "unset xtics\n" << std::endl;
    std::cout << "unset ytics\n" << std::endl;

    std::vector<int> n = { 100, 500, 2000, 10000, 500000, 1000000 };
    const int a = 100000;

    for (int i = 0; i < n.size(); i++) {
        double res = monte_carlo_pi(a, n[i]);
        std::cout << "set title \"n = " << n[i] << "; pi = " << res << "\"" << std::endl;
        printf("set size square\n");
        printf("set object %d rect from %d,%d to %d,%d\n", i + 1, 0, 0, a, a);
        printf("set object %d circle front at %f,%f size %f fillcolor rgb \"black\" lw 1\n", (i + 1 + n.size()), a / 2.0, a / 2.0, a / 2.0);
        printf("set yrange [0:%d]\n", a);
        printf("plot [0:%d] \"points_%d\" u 1:2:3 palette notitle\n", a, n[i]);
        printf("unset object\n");
    }

    return 0;
}