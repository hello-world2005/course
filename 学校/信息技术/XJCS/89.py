# 算了不写 Splay 了

n = int(input())
a = list(map(int, input().split()))
m = int(input())
for i in range(m):
  l, r = map(int, input().split())
  l -= 1
  r -= 1
  b = []
  for j in range(l, r + 1):
    b.append(a[j])
  b.reverse()
  for j in range(l, r + 1):
    a[j] = b[j - l]
for i in range(len(a) - 1):
  print(a[i], end = ' ')
print(a[-1])
