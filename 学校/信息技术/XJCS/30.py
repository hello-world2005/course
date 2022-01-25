n, r, q = map(int, input().split())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
c = [[i + 1, a[i], b[i]] for i in range(2 * n)]
for i in range(r):
  c.sort()
  c.sort(key = lambda x: x[1], reverse = True)
  for j in range(0, 2 * n, 2):
    if (c[j][2] > c[j + 1][2]):
      c[j][1] += 1
    else:
      c[j + 1][1] += 1 
  # print(c)
c.sort()
c.sort(key = lambda x: x[1], reverse = True)
print(c[q - 1][0])