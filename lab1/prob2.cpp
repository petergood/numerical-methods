#include <iostream>
#include <vector>
#include <stdio.h>
#include <chrono>

using namespace std;

#define MEASURE_TIME(FUNC) {\
    auto start = chrono::high_resolution_clock::now();\
    FUNC();\
    auto end = chrono::high_resolution_clock::now();\
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end - start);\
    printf("time: %f seconds\n\n", time_span.count());\
}

const int N = (int) 1e7;
const float val = 0.12345;
const float expectedResult = 1234500;

float kahan_sum(vector<float> v) {
    float sum = 0;
    float err = 0;
    for (float x : v) {
        float y = x - err;
        float tmp = sum + y;
        err = (tmp - sum) - y;
        sum = tmp;
    }

    return sum;
}

void execute_kahan() {
    vector<float> v;
    for (int i = 0; i < N; i++) {
        v.push_back(val);
    }

    float res = kahan_sum(v);
    float absoluteError = abs(res - expectedResult);
    float relativeError = abs(res - expectedResult) / expectedResult;
    printf("result: %f\n", res);
    printf("absolute error: %f\n", absoluteError);
    printf("relative error: %f\n", relativeError);
}

int main() {
    MEASURE_TIME(execute_kahan)

    return 0;
}