#include <iostream>
#include "aghMatrix.h"

template<typename T>
bool is_close_enough(AGHMatrix<T> prev, AGHMatrix<T> curr, double eps) {
    for (int i = 0; i < prev.get_rows(); i++) {
        if (abs(prev(i, 0) - curr(i, 0)) > eps) {
            return false;
        }
    }

    return true;
}

template<typename T>
AGHMatrix<T> jacobi(AGHMatrix<T> a, AGHMatrix<T> b) {
    int n = a.get_rows();
    AGHMatrix<T> x(n, 1, 0);
    AGHMatrix<T> L(n, n, 0);
    AGHMatrix<T> D(n, n, 0);
    AGHMatrix<T> U(n, n, 0);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) L(i, j) = a(i, j);
        for (int j = n - 1; j > i; j--) U(i, j) = a(i, j);
        D(i, i) = 1.0 / a(i, i);
    }

    AGHMatrix<T> M = D * (L + U) * (-1);
    AGHMatrix<T>* prev = nullptr;

    for (int i = 0; i < 100; i++) {
        AGHMatrix<T> tmp = (M * x) + (D * b);
        x = tmp;
        if (prev != nullptr && is_close_enough(*prev, tmp, 10)) break;
        x = tmp;
        prev = &x;
    }

    return x;
}

int main() {
    AGHMatrix<double> a({{ 4.0, -1.0, -0.2, 2.0 }, 
                            { -1.0, 5.0, 0, -2.0 }, 
                            { 0.2, 1.0, 10.0 -1.0 },
                            { 0, -2.0, -1.0, 4.0 }});

    AGHMatrix<double> b({{ 30.0, 0, -10.0, 5.0 }});

    std::cout << jacobi(a, b.transpose());

    return 0;
}