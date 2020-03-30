#include <iostream>
#include "aghMatrix.h"

template<typename T>
std::pair<AGHMatrix<double>, AGHMatrix<double>> doolittleDecomposition(AGHMatrix<T> mat) {
    if (mat.get_rows() != mat.get_cols()) {
        throw std::runtime_error("Matrix has to be sqare");
    }

    int n = mat.get_rows();
    AGHMatrix<T> u(n, n, 0);
    AGHMatrix<T> l(n, n, 0);
    for (int i = 0; i < n; i++) l(i, i) = 1;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            T s = 0;
            for (int k = 0; k < i; k++) {
                s += l(i, k) * u(k, j);
            }
            u(i, j) = mat(i, j) - s;
        }

        for (int j = i + 1; j < n; j++) {
            T s = 0;
            for (int k = 0; k < i; k++) {
                s += l(j, k) * u(k, i);
            }

            if (u(i, i) == 0) {
                throw std::runtime_error("Division by 0");
            }

            l(j, i) = (1.0 / u(i, i)) * (mat(j, i) - s);
        }
    }

    return std::make_pair(l, u);
}

int main() {
    AGHMatrix<double> mat({{ 5.0, 3.0, 2.0 }, 
                            { 1.0, 2.0, 0.0 }, 
                            { 3.0, 0.0, 4.0 }});

    auto res = doolittleDecomposition(mat);
    std::cout << res.first;
    std::cout << res.second;

    return 0;
}