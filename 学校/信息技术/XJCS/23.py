n = int(input())
m = int(input())
a = 0
vis = list(range(n))
for i in range(n):
  vis[i] = 0
for i in range(n - 1):
  print(i + 1, end = ' ')
print(n)
for i in range(2, n + 1):
  a = (a + m) % i
  for j in range(a, n):
    if vis[j] == 0:
      print(j + 1, end = ' ')
  for j in range(a):
    if vis[j] == 0:
      print(j + 1, end = ' ')
  print()
  vis[a] = 1
  # print(a + 1)
print(a + 1)
