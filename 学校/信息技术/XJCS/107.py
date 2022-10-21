a = list(map(int, input().split()))
dat, nxt = list(range(len(a) // 2)), list(range(len(a) // 2))
for i in range(0, len(a) - 1, 2): dat[i // 2] = a[i]; nxt[i // 2] = a[i + 1]
hd = a[-1]
i = hd
pre = 0
x = int(input())
flag = False
while (i != -1):
  if (dat[i] == x):
    flag = True
    if (i == hd):
      hd = nxt[i]
    else:
      nxt[pre] = nxt[i]
  pre = i
  i = nxt[i]
i = hd
if (flag):
  while (i != -1):
    print(dat[i], end = ' ')
    i = nxt[i]
  print()
else:
  print('未找到')