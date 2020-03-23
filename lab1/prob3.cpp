#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

float float_sum(int n, bool reverse) {
    float exp =  1.0 / 4;
    vector<float> v;
    for (int i = 0; i < n; i++) {
        v.push_back(exp);
        exp /= 2;
        printf("%.10f\n", v.back());
    }

    float sum = 0;

    if (reverse) {
        for (int i = n - 1; i >= 0; i--) {
            sum += v[i];
        }
    } else {
        for (int i = 0; i < n; i++) {
            sum += v[i];
        }
    }

    return sum;
}

double double_sum(int n, bool reverse) {
    double exp =  1.0 / 4;
    vector<double> v;
    for (int i = 0; i < n; i++) {
        v.push_back(exp);
        exp /= 2;
    }

    double sum = 0;

    if (reverse) {
        for (int i = n - 1; i >= 0; i--) {
            sum += v[i];
        }
    } else {
        for (int i = 0; i < n; i++) {
            sum += v[i];
        }
    }

    return sum;
}

int main() {
    float res = float_sum(50, false);
    float absoluteError = abs(0.5 - res);
    float relativeError = abs(0.5 - res) / 0.5;
    printf("result: %.10f\n", res);
    printf("absolute error: %.20f\n", absoluteError);
    printf("relative error: %.20f\n", relativeError);

    return 0;
}