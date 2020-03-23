#include <iostream>
#include <vector>
#include <chrono>
#include <stdio.h>

using namespace std;

vector<float> v;
const int N = 1e7;
const float x = 0.12345;
const float expectedResult = 1234500;

#define MEASURE_TIME(FUNC) {\
    auto start = chrono::high_resolution_clock::now();\
    FUNC();\
    auto end = chrono::high_resolution_clock::now();\
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end - start);\
    printf("time: %f seconds\n\n", time_span.count());\
}

float recursive_sum(int l, int r) {
    if (l > r) {
        return 0;
    }

    if (l == r) {
        return x;
    }

    int mid = (l + r) / 2;
    return recursive_sum(l, mid) + recursive_sum(mid + 1, r);
}

void compute_recursive_sum() {
    float recursiveResult = recursive_sum(0, N);
    float absoluteError = abs(expectedResult - recursiveResult);
    float relativeError = abs(expectedResult - recursiveResult) / expectedResult;
    printf("recursive result: %f\n", recursiveResult);
    printf("absolute error: %f\n", absoluteError);
    printf("relative error: %f\n", relativeError);
}

void compute_array_sum() {
    float sum = 0;
    int i = 0;
    const int reportStep = 25000;

    for (auto num : v) {
        sum += num;
        //if (i % reportStep == 0) printf("%f\n", sum);
        i++;
    }

    float absoluteError = abs(expectedResult - sum);
    float relativeError = abs(expectedResult - sum) / expectedResult;

    printf("iterative result: %f\n", sum);
    printf("relative error: %f\n", relativeError);
    printf("absolute error: %d\n", absoluteError);
}

int main() {
    for (int i = 0; i < N; i++) {
        v.push_back(x);
    }

    MEASURE_TIME(compute_array_sum)
    MEASURE_TIME(compute_recursive_sum)

    return 0;
}