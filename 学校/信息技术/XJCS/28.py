s = list(map(int, input().split()))
n, k, p = s[0], s[1], s[2]

a = list(i for i in range(0, k * 10))
ans = list()
x, y = 0, k
for i in range(1, k // n + 1):
  for j in range(1, n + 1):
    x += 1
    if (j == n):
      ans.append(a[x])
    for k in range(1, p + 1):
      x += 1
      y += 1
      a[y] = a[x]

ans.sort()

for i in range(len(ans)):
  print(ans[i])
