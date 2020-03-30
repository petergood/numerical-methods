# Lab2

Implementacja obliczania wyznacznika macierzy znajduje się w `gauss.cpp`.

### Porównanie algorytmów

W metodzie LU podstawowym problemem jest faktoryzacja macierzy na dwie macierze trójkątne - jedna jest
macierzą trójkątną górną, a druga dolną. Aby dokonać faktoryzacji korzystamy z metody Doolittla, w której
iteracyjnie (ze złożonością O(n^3)) obliczamy kolejne wartości w macierzach rozkładu. Dodatkowo, metoda działa tylko jeżeli  w macierzy trójkątniej górnej na przekątnej nie występuje 0 (w takiej sytuacji możemy spróbować zamienić dany rząd z innym - https://en.wikipedia.org/wiki/LU_decomposition). 

W metodzie Choleskiego
postępujemy podobnie, ale mamy dodatkowe ograniczenia, mianowicie rozkładana macierz musi być symetryczna
i dodatnio określona. Również macierz rozkładamy na macierz trójkątną górną i dolną, ale druga macierz jest transpozycją pierwszej. 

Metoda Jacobiego działa w inny sposób od powyższych algorytmów, mianowicie najpierw rozkładamy daną macierz na sumę trzech macierzy - trójkątnej górnej, dolnej i macierzy diagonalnej, a następnie po odpowiednich przekształceniach oblicza iteracyjnie wartości macierzy kolumnowej x, zaczynając od jakiegoś danego stanu początkowego. Kolejne wartości macierzy kolumnowej x zbiegają do poszukiwanego rozwiązania.