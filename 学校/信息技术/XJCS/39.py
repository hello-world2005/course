n = int(input())

a, b = 0, 1

for i in range(n - 1):
    c = a + b
    a, b = b, c

print(a)