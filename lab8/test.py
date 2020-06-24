import numpy as np

def DFT_slow(x):
    x = np.asarray(x, dtype=float)
    N = x.shape[0]
    n = np.arange(N)
    k = n.reshape((N, 1))
    M = np.exp(-2j * np.pi * k * n / N)
    return np.dot(M, x)

data = np.genfromtxt('daily-min-temperatures.csv', delimiter=",")
n = data.shape[0]
x = []

for i in range(1, n):
    x.append(data[i][1])

res = DFT_slow(x)
for r in res:
    print(abs(r))