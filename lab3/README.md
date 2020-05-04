# Lab 3 - Równania nieliniowe
## Funkcje testowe
```c++
typedef std::function<double(double)> func;

func f1 = [](double x) { return cos(x) * cosh(x) - 1; };
func f1_deriv = [](double x) { return cos(x) * sinh(x) - sin(x) * cosh(x); };

func f2 = [](double x) { return 1 / x - tan(x); };
func f2_deriv = [](double x) { return - 1 / (x * x) - (1 + tan(x) * tan(x)); };

func f3 = [](double x) { return pow(0.5, x) + exp(x) + 2 * cos(x) - 6; };
func f3_deriv = [](double x) { return exp(x) - pow(0.5, x) * log(2) - 2 * sin(x); };

struct result {
    double x;
    int iteration_count;
};
```

### Uwagi
Dla funkcji f2 przyjąłem przedział [10^-7, pi/2 - 10^-7], ponieważ wartość funkcji nie jest określona dla 0 i pi/2.

## Metoda bisekcji
Metoda biskecji polega na podziale przedziału na dwie równe części i sprawdzeniu znaku funkcji na krańcach przedziału. Na podstawie znaków ustalamy, czy miejsce zerowe znajduje się w lewym bądź prawym przedziale. Poprawność metody wynika z twierdzenia Cauchy'ego.
```c++
result bisection(func f, double left, double right, double eps) {
    if (f(left) * f(right) > 0) {
        throw std::runtime_error("Incorrect boundary values");
    }

    int iter_count = 0;

    while (std::abs(left - right) > eps) {
        double mid = (left + right) / 2;
        
        if (f(left) * f(mid) < 0) {
            right = mid;
        } else {
            left = mid;
        }

        iter_count++;
    } 

    result res;
    res.iteration_count = iter_count;
    res.x = left;
    return res;
}
```

Ilości iteracji potrzebne dla danej dokładności:

Dokładność: | f1 | f2 | f3
--- | --- | --- | ---
10^-7 | 21 | 21 | 21
10^-15 | 48 | 48 | 48
10^-33 | ? | ? | 54

Wartość *?* oznacza, że nie osiągnięta została zbieżność (najprawdopodobniej przez błąd typu double)

### Obliczenie pierwszych k pierwiastków f1
1. Ustalamy wartości l = 0, r = h, gdzie h jest wartością kroku (parametrem algorytmu)/
2. Zwiększamy r o h dopóki nie zostanie spełnione założenie metody bisekcji, czyli dopóki f(l)*f(r) < 0
3. Wykonujemy metodę bisekcji na przedziale [l, r] i wyznaczamy miejsce zerowe
4. Powtarzamy kroki 2 i 3 dla l = r, r = l + h

## Metoda Newtona

W metodzie Newtona na początku przyjumjemy wartość x0 a następnie obliczamy kolejne przybliżenia miejsca zerowego korzystając z zależności rekurencyjnej:

![eq](https://wikimedia.org/api/rest_v1/media/math/render/svg/26c32eb66fe40b1d1fb3309755823132a3ce61db)

Wzór wynika ze wzoru na prostą styczną do wykresu funkcji w danym punkcie. Wartość pochodnej można wyznaczyć analitycznie (w przypadku tego zadania pochodne obliczyłem przed wykonywaniem programu).

```c++
result newton(func f, func deriv, double left, double right, int max_iter, double eps) {
    double x = (left + right) / 2;
    double h = f(x) / deriv(x);
    int iter_count = 0;
    while (std::abs(h) >= eps && iter_count < max_iter) {
        h = f(x) / deriv(x);
        x = x - h;
        iter_count++;
    }

    result res;
    res.iteration_count = iter_count;
    res.x = x;
    return res;
} 
```

Dokładność: | f1 | f2 | f3
--- | --- | --- | ---
10^-7 | 6 | 3 | 4
10^-15 | 7 | 4 | 6
10^-33 | max | 5 | 7

Wartość *max* oznacza, że wymagana była maksymalna liczba iteracji (najprawdopodobniej przez błąd typu double).

Można zauważyć, że metoda Newtona szybciej zbiega do miejsca zerowego niż metoda bisekcji. Wynika to z tego, że w metodzie bisekcji w pesymistycznym przypadku będziemy mieli log(l - r) wykonań.

## Metoda siecznych

W metodzie siecznych korzystamy z założenia, że funkcja w dostatecznie małym przedziale zmienia się w sposób liniowy. Możemy wtedy w danym przedziale zastąpić krzywą sieczną, a przybliżona wartość miejsca zerowego jest równa punktowi przecięcia siecznej z osią OX. Przyjmując za x0 i x1 krańce przedziału [a, b] otrzymujemy zależność rekurencyjną na kolejne przybliżenia miejsca zerowego:

![eq](https://wikimedia.org/api/rest_v1/media/math/render/svg/09f942acd0fcae141747a73b52baaeef279b809f)

Metoda siecznych nad metodą Newtona ma tą zaletę, że nie wymaga obliczania pochodnej funkcji w danym punkcie.

```c++
result secant(func f, double left, double right, int max_iter, double eps) {
    double x1 = right;
    double x2 = left;
    int iter = 0;
    double prev_val = f((right + left) / 2);

    while (iter < max_iter) {
        double x = (x2 * f(x1) - x1 * f(x2)) / (f(x1) - f(x2));
        if (std::abs(prev_val - f(x1)) < eps) {
            break;
        }

        prev_val = f(x1);
        x2 = x1;
        x1 = x;
        iter++;
    }

    return { .x = x1, .iteration_count = iter };
}
```

Dokładność: | f1 | f2 | f3
--- | --- | --- | ---
10^-7 | 6 | 2 | 9
10^-15 | 7 | 8 | 11
10^-33 | 7 | ? | 12

Wartość *?* oznacza, że nie osiągnięta została zbieżność (najprawdopodobniej przez błąd typu double)

Metoda siecznych wypada nieco gożej niż metoda Newtona w ilości iteracji.