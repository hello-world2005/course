n, q1, q2 = map(int, input().split())
a = [0] * (n + 1)
b = [0] * (n + 1)
MOD = 1 << 32
for i in range(q1):
  s, x = map(int, input().split())
  _ = s
  j = 2
  fac = []
  while (j * j <= _):
    if (_ % j == 0): fac.append(j)
    while (_ % j == 0): _ //= j
    j += 1
  if (_ != 1): fac.append(_)
  for j in range(1 << len(fac)):
    k, cnt = 1, 0
    for l in range(0, len(fac)):
      if (j & (1 << l)): k *= fac[l]; cnt += 1
    a[k] = (a[k] + (-1) ** cnt * x) % MOD
# print(a)
su = [0] * (n + 1)
for i in range(1, n + 1):
  for j in range(i, n + 1, i):
    su[j] = (su[j] + a[i]) % MOD
for i in range(1, n + 1):
  for j in range(i, n + 1, i):
    b[i] = (b[i] + su[j]) % MOD
# print(b)
for i in range(q2):
  s = int(input())
  _ = s
  j = 2
  fac = []
  ans = 0
  while (j * j <= _):
    if (_ % j == 0): fac.append(j)
    while (_ % j == 0): _ //= j
    j += 1
  if (_ != 1): fac.append(_)
  for j in range(1 << len(fac)):
    k, cnt = 1, 0
    for l in range(0, len(fac)):
      if (j & (1 << l)): k *= fac[l]; cnt += 1
    ans = (ans + (-1) ** cnt * b[k]) % MOD
  print(ans)
