from random import randint
import sys
import os

# file = open('1.in', 'w')
x = sys.argv[1]
file = open('data/%s.in' % sys.argv[1], 'w')
n = randint(40000, 40000)
q = randint(10000, 10000)
file.write(str(n) + ' ' + str(q) + '\n')
a = [0] * n
amax = int(1e9)
for i in range(n): a[i] = randint(1, amax)
for i in range(n - 1): file.write(str(a[i]) + ' ')
file.write(str(a[-1]) + '\n')
for i in range(q):
   l = randint(1, n - 1)
   r = randint(l, n)
   file.write(str(l) + ' ' + str(r) + '\n')
file.close()
os.system('time ./stdd < data/%s.in > data/%s.ans' % (x, x))
