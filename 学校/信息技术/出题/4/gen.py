#without online
from random import randint

file = open('1.in', 'w')
# n = randint(39000, 40000)
n = randint(10000, 10000)
q = randint(39000, 40000)
file.write(str(n) + ' ' + str(q) + '\n')
a = [0] * n
for i in range(n): a[i] = randint(1, n)
for i in range(n - 1): file.write(str(a[i]) + ' ')
file.write(str(a[-1]) + '\n')
for i in range(q):
    l = randint(1, n - 1)
    r = randint(l, n)
    file.write(str(l) + ' ' + str(r) + '\n')
