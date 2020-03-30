#include <iostream>
#include <cmath>
#include "aghMatrix.h"

template<typename T>
AGHMatrix<double> choleskyDecomposition(AGHMatrix<T> mat) {
    if (!mat.is_symmetric()) {
        throw std::runtime_error("Matrix is not symmetric");
    }
    
    int n = mat.get_rows();
    AGHMatrix<double> l(n, n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (i == j) {
                T s = 0;
                for (int k = 0; k < i; k++) {
                    s += l(i, k) * l(i, k);
                }
                l(i, j) = sqrt(mat(i, j) - s);
            } else {
                T s = 0;
                for (int k = 0; k < i; k++) {
                    s += l(j, k) * l(i, k);
                }
                l(i, j) = (mat(i, j) - s) / l(j, j);
            }
        }
    }

    return l;
}

int main() {
    AGHMatrix<double> mat({{ 4.0, 12.0, -16.0 }, 
                            { 12.0, 37.0, -43.0 }, 
                            { -16.0, -43.0, 98.0 }});

    std::cout << choleskyDecomposition(mat);

    return 0;
}