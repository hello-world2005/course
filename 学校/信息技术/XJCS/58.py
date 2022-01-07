import io
import os
import sys
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

n = int(input())
a = list(map(int, input().split()))
a.insert(0, 'qwq')
a.append('qaq')
hd = list()
pre = list(range(n + 2))
nxt = list(range(n + 2))
pre[0], nxt[0] = -1, 1
pre[n + 1], nxt[n + 1] = n, n + 2
for i in range(1, n + 1):
  if (a[i] != a[i - 1]):
    hd.append(i)
  pre[i] = i - 1
  nxt[i] = i + 1

while (nxt[0] != n + 1):
  ans = ''
  _ = list()
  for i in hd:
    pre[nxt[i]] = pre[i]
    nxt[pre[i]] = nxt[i]
    ans += str(i) + ' '
    if (a[i] != a[pre[i]] and a[i] == a[nxt[i]]):
      _.append(nxt[i])
  sys.stdout.write(ans + '\n')
  hd = _