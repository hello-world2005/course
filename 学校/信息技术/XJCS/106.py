a = list(map(int, input().split()))
dat, nxt = list(range(len(a) // 2)), list(range(len(a) // 2))
for i in range(0, len(a) - 1, 2): dat[i // 2] = a[i]; nxt[i // 2] = a[i + 1]
#hd = a[-1]
#i = hd
#while (i != -1):
#  print(dat[i], end = ' ')
#  i = nxt[i]
#print()
x = int(input())
dat.append(x)
dat.sort()
for i in dat:
  print(i, end = ' ')
print()