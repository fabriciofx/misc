# Precisa instalar o python3 e a matplotlib
import time
import matplotlib.pyplot as plt

# Questão retirada do link abaixo
# http://www.lapix.ufsc.br/ensino/estrutura-de-dados/complexidade-de-algoritmos/

input = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160,
    170, 180, 190, 200]
output = []

# Perform the algorithm
print("n;time")
for n in input:
    x = []

    for s in range(1, n ** 2):
        x.append(s)

    start_time = time.time()
    for i in range(1, n - 2):
        for j in range(1, 2 * n):
            if (i  % 2) != 0:
                for k in range(1, n ** 2):
                    x[k - 1] = x[i - 1] * x[i - 1]
            else:
                for k in range(1, n):
                    x[k - 1] = j
            x[j - 1] = 1
            x[i - 1] = j

    end_time = time.time()
    elapsed = end_time - start_time
    output.append(elapsed)
    print(n, ";", elapsed)

# Plot the graph
plt.plot(input, output)
plt.xlabel('n')
plt.ylabel('time')
plt.title('Complexity')
plt.savefig('complexity.png')
