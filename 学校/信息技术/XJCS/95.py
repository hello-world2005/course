a = list(map(int, input().split()))
a.append(0)
l, r = 0, 0
for i in range(1, len(a)):
  if (a[i] == a[i - 1] + 1):
    r += 1
  else:
    if (l == r): print(a[l], end = ' ')
    else: print("%d->%d"%(a[l], a[r]), end = ' ')
    l = r = i
print()
