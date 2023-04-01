n, m = map(int, input().split())
a = {}
for i in range(n):
  s = input().split()
  a[s[0]] = [int(s[1])] + list(map(float, s[2:]))
ions = {}
# print(a)
for i in range(m):
  s = input().split()
  salt = s[0] + '('
  tmp = True
  cnt = ''
  qwq = ''
  ionn = {}
  for j in range(len(salt)):
    if (salt[j] == '('):
      tmp = True
      if (cnt == ''): cnt = 1
      if (qwq != ''):
        if (not qwq in ionn): ionn[qwq] = int(cnt)
        else: ionn[qwq] += int(cnt)
      qwq = ''
      cnt = ''
    elif salt[j] == ')':
      tmp = False
    else:
      if (tmp): qwq += salt[j]
      else: cnt += salt[j]
  for j in ionn:
    if (not j in ions): ions[j] = float(s[1]) * ionn[j]
    else: ions[j] += float(s[1]) * ionn[j]
l = -20.0; r = 20.0
# print(ions)
# print(a)

def Cal(ion, ph) -> float:
  if (ion == 'H' or ion == 'OH'): return 0.0
  b, c, d = 0.0, 0.0, 1.0
  if (a[ion][0] > 0):
    for i in range(a[ion][0], 0, -1):
      b += d
      c += i * d
      d *= (10 ** (ph - 14)) / (10 ** (-a[ion][i]))
    b += d
  else:
    for i in range(-a[ion][0], 0, -1):
      b += d
      c += i * d
      d *= (10 ** (-ph)) / (10 ** (-a[ion][i]))
    b += d
    c = -c
  return ions[ion] * c / b

while (abs(l - r) > 1e-4):
  m = (l + r) / 2
  s = 0.0
  for i in ions:
    s += Cal(i, m)
  s += 10 ** (-m) - 10 ** (m-14)
  # print(m, s)
  if (s > 0): l = m
  else: r = m
print("%.2f" % (m))
