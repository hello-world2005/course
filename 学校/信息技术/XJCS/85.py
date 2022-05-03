import io
import os
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

import heapq
n, m = map(int, input().split())
e = [[]for i in range(n + 1)]
deg = [0 for i in range(n + 1)]
for i in range(m):
  u, v = map(int, input().split())
  e[u].append(v)
  deg[v] += 1
for i in range(1, n + 1):
  e[i].sort()
s = 0
for i in range(1, n + 1):
  if (deg[i] == 0):
    s = i
    break
q = []
heapq.heappush(q, s)
ans = []
while (len(q)):
  u = heapq.heappop(q)
  ans.append(u)
  for v in e[u]:
    if (deg[v] == -1):
      continue
    deg[v] -= 1
    if (deg[v] == 0):
      deg[v] = -1
      heapq.heappush(q, v)
for i in range(len(ans) - 1):
  print(ans[i], end = ' ')
print(ans[-1])

