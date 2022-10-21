a = list(map(int, input().split()))
#2 86 34 75 8 4 59 67 68 93
#5 9  6  1  2 4 7  8  3  -1
dat, nxt = list(range(len(a))), list(range(len(a)))
for i in range(0, len(a) - 1, 2): dat[i // 2] = a[i]; nxt[i // 2] = a[i + 1]
i = a[-1]
while (i != -1):
  print(dat[i], end = ' ')
  i = nxt[i]
print()