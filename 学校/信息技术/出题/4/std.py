from bisect import bisect_left
from math import ceil

N = int(4e4 + 10)
M = int(2e2 + 10)

bl = [0] * M
br = [0] * M
blg = [0] * N
rev = [0] * M

# x & (-x)

v = [[0] * N for i in range(M)]
s = [[0] * N for i in range(M)]

def lowbit(i): return i & (-i)

def Add1(bk, p, k):
  while (p <= n):
    v[bk][p] += k
    p += lowbit(p)

def Sum1(bk, p):
  res = 0
  while (p):
    res += v[bk][p]
    p -= lowbit(p)
  return res

def Sum2(bk, p):
  res = 0
  while (p):
    res += s[bk][p]
    p -= lowbit(p)
  return res

cot = [[0] * M for i in range(M)]   # contribute
sc = [[0] * M for i in range(M)]    # sum contribute

def Solve(l, r):
  ans = 0
  lbl = blg[l]; rbl = blg[r]
  qwq = [0] * (n + 10)
  def add(p):
    while (p <= n):
      qwq[p] += 1
      p += lowbit(p)
  def sum(p):
    res = 0
    while (p):
      res += qwq[p]
      p -= lowbit(p)
    return res
  if (lbl == rbl):
    for i in range(l, r + 1):
      ans += (i - l) - sum(a[i]); add(a[i])
      # for j in range(1, n + 1): print(sum(j), end = ' ')
      # print()
    return ans
  ans += sc[lbl + 1][rbl - 1]
  for i in range(l, br[lbl] + 1):
    ans += Sum2(rbl - 1, a[i] - 1) - Sum2(lbl, a[i] - 1)
  for i in range(br[rbl - 1], r + 1):
    ans += br[rbl - 1] - bl[lbl + 1] + 1 - (Sum2(rbl - 1, a[i]) - Sum2(lbl, a[i]))
  for i in range(bl[rbl], r + 1): add(a[i])
  for i in range(l, br[lbl] + 1): ans += sum(a[i] - 1)
  for i in range(n + 10): qwq[i] = 0
  for i in range(l, br[lbl] + 1): add(a[i])
  for i in range(bl[rbl], r + 1): ans += (br[lbl] - l + 1) - sum(a[i])
  for i in range(n + 10): qwq[i] = 0
  for i in range(l, br[lbl] + 1): ans += (i - l) - sum(a[i]); add(a[i])
  for i in range(n + 10): qwq[i] = 0
  for i in range(bl[rbl], r + 1): ans += (i - bl[rbl]) - sum(a[i]); add(a[i])
  return ans

if __name__ == '__main__':
  n, q = map(int, input().split())
  a = list(map(int, input().split())); b = a
  b = list(set(b)); b.sort()
  for i in range(n):
    a[i] = bisect_left(b, a[i]) + 1
  # print(a)
  m = int(ceil(n / M))
  br[-1] = -1
  for i in range(m):
    bl[i] = br[i - 1] + 1
    br[i] = min(M * (i + 1) - 1, n - 1)
    # print(bl[i], br[i])
    for j in range(bl[i], br[i] + 1):
      blg[j] = i
      rev[i] += (j - bl[i]) - Sum1(i, a[j])
      Add1(i, a[j], 1)
  for i in range(n): s[0][i] = v[0][i]
  for i in range(1, m):
    for j in range(n):
      s[i][j] = s[i - 1][j] + v[i][j]
  for i in range(m):
    for j in range(i + 1, m):
      for k in range(bl[i], br[i] + 1):
        cot[i][j] += br[j] - bl[j] + 1 - Sum1(j, a[k])
  # for i in range(m):
  #   for j in range(i + 1, m):
  #     print(cot[i][j], end = ' ')
  #   print()
  # print(sc[1][0])
  for i in range(m):
    for j in range(i + 1, m):
      sc[i][j] = rev[i]
      for k in range(i + 1, j + 1):
        sc[i][j] += cot[i][k]
  last_ans = 0
  while (q):
    q -= 1
    ll, rr = map(int, input().split())
    # l = ll ^ last_ans
    # r = rr ^ last_ans
    # if (l > r): l, r = r, l
    l, r = ll - 1, rr - 1
    last_ans = Solve(l, r)
    print(last_ans)
