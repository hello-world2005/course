n = int(input())
m = int(input())
a = 0
for i in range(2, n + 1):
  a = (a + m) % i
print(a + 1)