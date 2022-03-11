n = int(input())
a = list(range(n))
for i in range(n):
  a[i] = list(map(int, input().split()))
lev = int(input())
for i in range(n):
  s = 0
  k = 0
  for j in a[i]:
    s += j
    if (j >= lev):
      k += 1
  ave = s / len(a[i])
  per = k / len(a[i])
  print(chr(i + 65), round(ave, 2), str(round(per * 100, 2)) + '%')