#include <iostream>
#include <cmath>

using namespace std;

float compute_e(float exp) {
    float sum = 1;
    float lastsum = 0;
    float num = exp;
    long long fact = 1;
    long long i = 2;

    while (abs(abs(lastsum) - abs(sum)) > 1e-3) {
        lastsum = sum;
        sum += num / fact;
        num *= exp;
        fact = fact * i++;
    }

    return sum;
}

int main() {
    printf("%.7f\n", compute_e(-5.5));
    printf("%.7f\n", 1 / compute_e(5.5));

    return 0;
}