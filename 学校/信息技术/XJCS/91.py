n, m, q = map(int, input().split())
a = [0 for i in range(n)]

for i in range(n):
  a[i] = input()

for k in range(q):
  x, y = map(int, input().split())
  x -= 1; y -= 1
  a[x], a[y] = a[y], a[x]

for i in range(n):
  print(a[i])
