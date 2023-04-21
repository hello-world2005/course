from bisect import bisect_left

n, q = map(int, input().split())
a = list(map(int, input().split()))
b = list(set(a)); b.sort()
for i in range(n):
  a[i] = bisect_left(b, a[i]) + 1
qwq = [0] * (n + 1)
def lowbit(i): return i & (-i)
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
last_ans = 0
while (q):
  q -= 1
  ans = 0
  l, r = map(int, input().split())
  ll = (l ^ last_ans - 1) % n + 1
  rr = (r ^ last_ans - 1) % n + 1
  if (ll > rr): ll, rr = rr, ll
  l, r = ll, rr
  l -= 1; r -= 1
  for i in range(0, n + 1): qwq[i] = 0
  for i in range(l, r + 1):
    ans += (i - l) - sum(a[i]); add(a[i])
  last_ans = ans
  print(ans)