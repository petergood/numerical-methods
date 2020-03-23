#include <iostream>

using namespace std;

float compute_eps() {
    float eps = 0.5;
    float prev = 0;

    while (1 + eps != 1.0) {
        prev = eps;
        eps /= 2;
    }

    return prev;
}

int main() {
    float eps = compute_eps();
    cout << "eps: " << eps << endl;

    return 0;
}