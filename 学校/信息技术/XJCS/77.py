n = int(input())
maxn = 0
idx = -1
for i in range(n):
  a = list(map(int, input().split()))
  for j in a:
    if (j > maxn):
      maxn = j
      idx = i
print(chr(idx + 65), maxn)