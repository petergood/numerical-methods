#include <iostream>
#include <cmath>
#include "aghMatrix.h"

enum SystemSolution { INF, ONE, ZERO };

template<typename T>
SystemSolution to_echelon_form(AGHMatrix<T> &mat) {
    int n = mat.get_rows();

    // powtarzamy redukcję dla każdej niewiadomej
    for (int k = 0; k < n; k++) {
        // znajdujemy wiersz, w której współ. przy k-tej niewiadomej ma największą wartość bezwzględną
        // moglibyśmy wybrać dowolny wiersz, w którym współ. przy k-tej niewiadomej ma niezerową wartość,
        // ale wybranie wartości z największą wartością bezwzględną sprawia, że algorytm jest bardziej 
        // stabilny numerycznie.
        int mx = k;
        for (int i = k; i < n; i++) {
            if (abs(mat(i, k)) > abs(mat(mx, k))) {
                mx = i;
            }
        }

        // znaleziony wiersz zamieniamy z aktualnym
        mat.swap_rows(k, mx);

        // maksymalna wartość współ. przy k-tej niewiadomej jest równa zero
        // (z tego wynika, że wszystkie są równe zero)
        if (mat(k, k) == 0) {
            // z Tw. Kroneckera-Capellego
            return mat(k, n) != 0 ? ZERO : INF;
        }

        // dla wierszy niżej
        for (int i = k + 1; i < n; i++) {
            // wartość, przez którą będziemy mnożyć k-ty wiersz, aby wyzerować k-ty współczynnik
            // w i-tym wierszu
            double f = mat(i, k) / mat(k, k);

            for (int j = k + 1; j < mat.get_cols(); j++) {
                // od każdego współczynnika odejmujemy k-ty wiersz pomnożony przez f
                mat(i, j) -= mat(k, j) * f;
            }

            // zerujemy współczynnik (robimy to poza pętlą aby uniknąć uzyskania małej liczby zmiennoprzecinkowej w
            // wyniku niedokładności)
            mat(i, k) = 0;
        }
    }

    return ONE;
}

template<typename T>
AGHMatrix<T> get_res(AGHMatrix<T> echelonMat) {
    int n = echelonMat.get_rows();
    AGHMatrix<T> res(n, 1, 0);

    // zaczynamy od końca (mamy jedną niewiadomą)
    for (int k = n - 1; k >= 0; k--) {
        // sumujemy kombinacje poprzednio obliczonych niewiadomych
        T s = 0;
        for (int i = k + 1; i < n; i++) {
            s += echelonMat(k, i) * res(i, 0);
        }

        // obliczamy wartość k-tej niewiadomej
        res(k, 0) = (echelonMat(k, n) - s) / echelonMat(k, k);
    }

    return res.transpose();
}

template <typename T>
double det(AGHMatrix<T> mat) {
    if (mat.get_rows() != mat.get_cols()) {
        throw std::runtime_error("Matrix must be square");
    }

    to_echelon_form(mat);
    double d = mat(0, 0);

    for (int i = 1; i < mat.get_rows(); i++) {
        d *= mat(i, i);
    }

    return d;
}

int main() {
    AGHMatrix<double> mat({{ 2.0, 1.0, -1.0, 8.0 }, 
                            { -3.0, -1.0, 2.0, -11.0 }, 
                            { -2.0, 1.0, 2.0, -3.0 }});

    std::cout << to_echelon_form(mat) << std::endl;
    std::cout << mat << std::endl;
    std::cout << get_res(mat);

    return 0;
}