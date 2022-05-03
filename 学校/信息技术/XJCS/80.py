n, m = map(int, input().split())

t, lazy = [0] * (n * 4 + 10), [0] * (n * 4 + 10)

def PushUp(rt):
  t[rt] = t[rt * 2] + t[rt * 2 + 1]

def PushDown(rt, l, r):
  if (lazy[rt]):
    mid = (l + r) // 2
    lc = rt * 2
    rc = rt * 2 + 1
    t[lc] += lazy[rt] * (mid - l + 1)
    t[rc] += lazy[rt] * (r - mid)
    lazy[lc] += lazy[rt]
    lazy[rc] += lazy[rt]
    lazy[rt] = 0

def Update(rt, l, r, ql, qr, k):
  if (ql <= l and r <= qr):
    t[rt] += (r - l + 1) * k
    lazy[rt] += k
    return
  if (lazy[rt]):
    PushDown(rt, l, r)
  mid = (l + r) // 2
  lc = rt * 2
  rc = rt * 2 + 1
  if (ql <= mid):
    Update(lc, l, mid, ql, qr, k)
  if (qr > mid):
    Update(rc, mid + 1, r, ql, qr, k)
  PushUp(rt)

def Query(rt, l, r, ql, qr):
  if (ql <= l and r <= qr):
    return t[rt]
  if (lazy[rt]):
    PushDown(rt, l, r)
  mid = (l + r) // 2
  res = 0
  lc = rt * 2
  rc = rt * 2 + 1
  if (ql <= mid):
    res += Query(lc, l, mid, ql, qr)
  if (qr > mid):
    res += Query(rc, mid + 1, r, ql, qr)
  return res

for i in range(m):
  s = input().split()
  opt = int(s[0])
  if (opt == 1):
    l, r, k = map(int, s[1:])
    Update(1, 1, n, l, r, k)
  else:
    l, r = map(int, s[1:])
    print(Query(1, 1, n, l, r))