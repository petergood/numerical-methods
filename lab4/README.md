# Laboratorium 4 - Interpolacja

## Wstęp
Interpolacja funkcji F polega na wyznaczeniu takiej funkcji interpolacyjnej, która w określonych z góry punktach przyjmuje wartości równe funkcji F. Takie punkty nazywamy węzłami.

W każdej metodzie mamy *n* punktów postaci (*x<sub>i</sub>*, *y<sub>i</sub>*).

## Funkcja testowa
```c++
typedef std::function<double(double)> func;

func f1 = [](double x) { return sin(5 * x / M_PI) * exp(-1 * x / M_PI); };
func f1_deriv = [](double x) { return (exp(-1 * x / M_PI) * (5 * cos(5 * x / M_PI) - sin(5 * x / M_PI))) / M_PI; };
```

## Metody ustalania węzłów

### Punkty równoodległe
```c++
std::vector<double> fixed_step(int n, double a, double b) {
    std::vector<double> points;
    double h = (b - a) / n;
    for (int i = 0; i < n; i++) {
        points.push_back(a + i * h);
    }
    return points;
}
```

### Punkty Czebyszewa
N punktów Czebyszewa w przedziale *[a, b]* wyznaczamy ze wzoru:

![asd](http://www.sciweavers.org/upload/Tex2Img_1588521153/render.png)

```c++
std::vector<double> chebyshev_nodes(int n, double a, double b) {
    std::vector<double> points;
    for (int k = 1; k <= n; k++) {
        points.push_back(0.5 * (a + b) + 0.5 * (b - a) * cos(((2.0 * k - 1) / (2 * n)) * M_PI));
    }
    return points;
}
```

## Metoda Newtona
Metoda Newtona sprowadza się do wyznaczenia wielomianu interpolacyjnego Newtona, czyli wielomianu postaci (kombinacja liniowa wielomianów z bazy):

![asd](https://wikimedia.org/api/rest_v1/media/math/render/svg/b7bb15443c96172a7ef235cb973010feab25e428)

Gdzie funkcja *n* jest zdefiniowana jako:

![asd](https://wikimedia.org/api/rest_v1/media/math/render/svg/227efa64e8b5301108a7a5da5cbbb86dcf59af04)

Współczynniki *a* zdefiniowane są za pomocą różnicy dzielonej

![asd](https://wikimedia.org/api/rest_v1/media/math/render/svg/f40744c93b8380df3b93026cedb3e03e51e3dd2e)

Aby wyznaczyć różnice dzielone, tworzymy tabelę o rozmiarze n x n, za pomocą której wyznaczamy kolejne współczynniki.

```c++
double newton_function(int n, std::vector<double> points, func f, double x) {
    std::vector<std::vector<double>> table;

    for (int i = 0; i < n; i++) {
        table.push_back(std::vector<double>());
        table[i].push_back(f(points[i]));
        for (int j = 1; j < n; j++) {
            table[i].push_back(0);
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= i; j++) {
            table[i][j] = (table[i][j - 1] - table[i - 1][j - 1]) / (points[i] - points[i - j]);
        }
    }

    double y = 0;
    
    for (int i = 0; i < n; i++) {
        double a = table[i][i];

        for (int j = 0; j < i; j++) {
            a *= x - points[j];
        }

        y += a;
    }

    return y;
}
```

![2](https://i.imgur.com/lbH9O46.png)
![5](https://i.imgur.com/Sfy1tva.png)
![10](https://i.imgur.com/sVLT7iG.png)
![20](https://i.imgur.com/nGAECNW.png)
![40](https://i.imgur.com/i1rG2q9.png)

### Pomiar błędu
Aby zmierzyć błąd próbkowałem dużą ilość punktów i obliczałem różnicę bezwzględną między wartościami funkcji i wielomianu interpolacyjnego.

N | w. równoodległe | w. Czebyszewa
--- | --- | ---
2 | 3862.92 | 5537.57
5 | 2659.16 | 2157
10 | 5101.04 | 2012.88
20 | 2440.15 | 23.8141
40 | ~5e-3 | ~9e-6
... | 
70 | 70291.7 | 149.717 

Dla N = 70 możemy zaobserwować **efekt Runge’go**, czyli pogorszenie jakości interpolacji mimo zwiększenia liczby równoodległych węzłów. Aby uniknąć efektu Runge’go możemy użyć węzłów Czebyszewa, gdzie węzły są bliżej siebie na krańcach przedziału (chociaż w moich pomiarach można zaobserwować pogorszenie się dokładności).


## Metoda Lagrange’a
W metodzie Lagrange'a musimy wyznaczyć wielomian postaci:

![asd](https://wikimedia.org/api/rest_v1/media/math/render/svg/7efe6f4a9d0e9a6cf53f0edba71b8ee940b53a86)

Wartości tego wielomianu będą równe wartościom funkcji interpolowanej f we wszystkich węzłach (*x<sub>i</sub>*, *y<sub>i</sub>*).

```c++
double lagrange_function(func f, std::vector<double> points, int n, double x) {
    double y = 0;

    for (int i = 0; i < n; i++) {
        double a = f(points[i]);
        
        for (int j = 0; j < n; j++) {
            if (i != j) {
                a *= (x - points[j]) / (points[i] - points[j]);
            }
        }

        y += a;
    }

    return y;
}
```

![2](https://i.imgur.com/3l8A5E6.png)
![5](https://i.imgur.com/bjjkmaP.png)
![10](https://i.imgur.com/gZq6oIx.png)
![30](https://i.imgur.com/aL8nfOh.png)
![40](https://i.imgur.com/IHTWHti.png)

### Pomiar błędu

N | w. równoodległe | w. Czebyszewa
--- | --- | ---
2 | 3862.92 | 5537.57
5 | 2659.16 | 2157
10 | 5101.04 | 2012.88
30 | 15.617 | ~1e-3
40 | ~4e-4 | ~6e-10
... | 
70 | 184277 | ~3e-12

Dla N = 70 obserwujemy efekt Runge’go. Użycie węzłów Czebyszewa daje lepszy rezultat.

## Interpolacja Hermite’a

W interpolacja Hermite'a wymagamy, aby w węzłach równe były wartości funkcji interpolowanej i interpolacyjnej, jak i *m* pierwszych pochodnych tych funkcji. W mojej implementacji ograniczyłem się do nałożenia warunku równości tylko pierwszej pochodnej. Aby ustalić wielomian interpolacyjny możemy postępować podobnie jak w przypadku metody Newtona, to znaczy tworzymy nowy zbiór węzłów

![asd](https://wikimedia.org/api/rest_v1/media/math/render/svg/a5282c240e91c66f3305772eeb79fe29ac8a2c5d)

Taki, że:

![asd](https://wikimedia.org/api/rest_v1/media/math/render/svg/c71503b1c444ba1b0cca6c157baa686777bcb213)

Następnie ustalamy wielomian interpolacyjny Newtona dla nowego zbioru węzłów, z dodatkowym ograniczeniem, że wartość różnicy dzielonej [z<sub>i</sub>, z<sub>i + 1</sub>] jest równa *f<sup>'</sup>(x<sub>i</sub>)*.

```c++
double hermite_function(int n, func f, func f_deriv, std::vector<double> points, double x) {
    std::vector<std::vector<double>> table;
    std::vector<double> z;

    for (int i = 0; i < n; i++) {
        std::vector<double> row;
        row.push_back(f(points[i]));

        for (int j = 1; j < 2 * n; j++) {
            row.push_back(0);
        }

        table.push_back(row);
        table.push_back(std::vector<double>(row));
    
        z.push_back(points[i]);
        z.push_back(points[i]);
    }

    for (int i = 1; i < 2 * n; i++) {
        for (int j = 1; j <= i; j++) {
            if (j == 1 && i % 2 == 1) {
                table[i][j] = f_deriv(z[i]);
            } else {
                table[i][j] = (table[i][j - 1] - table[i - 1][j - 1]) / (z[i] - z[i - j]);
            }
        }
    }

    double res = 0;

    for (int k = 0; k < 2 * n; k++) {
        double a = table[k][k];

        for (int i = 0; i < k; i++) {
            a *= x - z[i];
        }

        res += a;
    }

    return res;
}
```

![2](https://i.imgur.com/srStFvx.png)
![5](https://i.imgur.com/Tqo8rwO.png)
![10](https://i.imgur.com/xseu7VR.png)
![20](https://i.imgur.com/IcTgAmZ.png)

### Pomiar błędu

N | w. równoodległe | w. Czebyszewa
--- | --- | ---
2 | 113886 | 5731.33
5 | 369884 | 3157.49
10 | 155735 | 37.3185
20 | 0.0031319 | ~1e-05
... | 
35 | 484500 | 4.0341

Dla N = 35 możemy zaobserwować efekt Runge’go. 