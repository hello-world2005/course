from bisect import bisect_left
from functools import cmp_to_key

N = int(4e4 + 10)
M = int(2e2 + 10)

n = 0

blg = [0] * N

f = [[0 for j in range(M)] for i in range(M)]

# x & (-x)

v = [0 for i in range(N)]
p = [0 for i in range(N)]
q = [0 for i in range(N)]

def cmp(x, y):
  if (a[x] > a[y]): return 1
  return -1

def lowbit(i): return i & (-i)

def Add(p, k):
  while (p):
    v[p] += k
    p -= lowbit(p)

def Sum(p):
  res = 0
  while (p <= n):
    res += v[p]
    p += lowbit(p)
  return res

cot = [0 for i in range(M)]
sc = [[0] * M for i in range(N)]    # sum contribute

c = [0 for i in range(N)]
d = [0 for i in range(N)]

def Work(qaq, qwq):
  i, j = 1, 1
  ans = 0
  while (i <= qaq and j <= qwq):
    if (c[i] <= d[j]): i += 1
    else: j += 1; ans += qaq - i + 1
  return ans

def Solve(x, l, r):
  ans = p[r] - (0 if (l == (x - 1) * M + 1) else p[l - 1])
  # print('>>', ans)
  qaq, qwq = 0, 0
  for i in range((x - 1) * M + 1, min(x * M, n) + 1):
    if (b[i] < l): qaq += 1; c[qaq] = a[b[i]]
  for i in range((x - 1) * M + 1, min(x * M, n) + 1):
    if (b[i] >= l and b[i] <= r): qwq += 1; d[qwq] = a[b[i]]
  ans -= Work(qaq, qwq)
  return ans

if __name__ == '__main__':
  n, m = map(int, input().split())
  a = list(map(int, input().split()))
  a = [0] + a
  b = a
  b = list(set(b)); b.sort()
  for i in range(1, n + 1):
    a[i] = bisect_left(b, a[i])
  for i in range(1, n + 1): blg[i] = (i - 1) // M + 1
  b = [i for i in range(n + 1)]
  # for i in range(1, n + 1): b[i] = i
  b[1:n + 1] = sorted(b[1:n + 1], key = cmp_to_key(cmp))
  # print(b)
  i = 1
  while (i <= n):
    t = a[b[i]]; j = i
    while (i <= n and a[b[i]] == t):
      for k in range(blg[b[i]] + 1, blg[n] + 1): sc[b[i]][k] = cot[k]
      i += 1
    for k in range(j, i): cot[blg[b[k]]] += 1
  for i in range(1, blg[n] + 1): cot[i] = 0
  b[1:n + 1].reverse()
  c = b[1:n + 1]
  c.reverse()
  b[1:n + 1] = c
  # print(b)
  i = 1
  while (i <= n):
    t = a[b[i]]
    j = i
    while (i <= n and a[b[i]] == t):
      for k in range(1, blg[b[i]]): sc[b[i]][k] = cot[k]
      i += 1
    for k in range(j, i): cot[blg[b[k]]] += 1
  for j in range(1, blg[n] + 1):
    for i in range((j - 1) * M, 0, -1):
      if (i % M != 0): sc[i][j] += sc[i + 1][j]
  for j in range(1, blg[n] + 1):
    for i in range(j * M + 1, n + 1):
      if (i % M != 1): sc[i][j] += sc[i - 1][j]
  for i in range(1, n + 1):
    for j in range(1, blg[n] + 1): sc[i][j] += sc[i][j - 1]
  for j in range(1, blg[n] + 1):
    for i in range(0, n + 1): v[i] = 0
    l = 0
    for i in range((j - 1) * M + 1, min(j * M, n) + 1):
      l += Sum(a[i] + 1)
      p[i] = l
      Add(a[i], 1)
    for i in range(0, n + 1): v[i] = 0
    l = 0
    for i in range(min(j * M, n), (j - 1) * M, -1):
      l += Sum(n - a[i] + 2)
      q[i] = l
      Add(n - a[i] + 1, 1)
  for i in range(n + 1): b[i] = i
  for i in range(1, blg[n] + 1):
    l = (i - 1) * M + 1
    r = min(i * M, n)
    b[l: r + 1] = sorted(b[l: r + 1], key = cmp_to_key(cmp))
  for i in range(1, blg[n] + 1): f[i][i] = p[min(i * M, n)]
  for i in range(1, blg[n]):
    for j in range(i + 1, blg[n] + 1):
      qaq = 0
      for k in range((i - 1) * M + 1, i * M + 1): qaq += 1; c[qaq] = a[b[k]]
      qwq = 0
      for k in range((j - 1) * M + 1, min(j * M, n) + 1): qwq += 1; d[qwq] = a[b[k]]
      f[i][j] = Work(qaq, qwq)
  for i in range(blg[n] - 1, 0, -1):
    for j in range(i + 1, blg[n] + 1):
      f[i][j] += f[i][j - 1] + f[i + 1][j] - f[i + 1][j - 1]
  # for i in range(1, blg[n] + 1):
  #   for j in range(1, blg[n] + 1):
  #     print(f[i][j], end = ' ')
  #   print()
  ans = 0
  while (m):
    m -= 1
    # ll, rr = map(int, input().split())
    l, r = map(int, input().split())
    ll = (l ^ ans - 1 + n) % n + 1
    rr = (r ^ ans - 1 + n) % n + 1
    if (ll > rr): ll, rr = rr, ll
    l, r = blg[ll], blg[rr]
    if (l == r):
      # print(l, ll, rr)
      ans = Solve(l, ll, rr)
      print(ans)
      continue
    ans = f[l + 1][r - 1]
    ans += q[ll] + p[rr]
    tp = 0
    qaq, qwq = 0, 0
    for i in range((l - 1) * M + 1, l * M + 1):
      if (b[i] >= ll): qaq += 1; c[qaq] = a[b[i]]
    for i in range((r - 1) * M + 1, min(r * M, n) + 1):
      if (b[i] <= rr): qwq =+ 1; d[qwq] = a[b[i]]
    ans += Work(qaq, qwq)
    ans += sc[ll][r - 1] - sc[ll][l] + sc[rr][r - 1] - sc[rr][l]
    print(ans)
