from numpy import genfromtxt

data = genfromtxt('daily-min-temperatures.csv', delimiter=",")
n = data.shape[0]

print(n)

for i in range(1, n):
    print(data[i, 1])