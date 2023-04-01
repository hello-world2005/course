while True:
  s = input().split()
  n = int(s[0])
  if (n == 0): break
  a = [0 for i in range(n + 10)]
  for i in range(n):
    a[i] = int(s[i + 1])
  st, tp = [0 for i in range(n + 10)], 0
  w = [0 for i in range(n + 10)]
  ans = 0
  for i in range(n):
    # print(i, tp, st, w)
    if (tp == 0 or a[i] > st[tp - 1]):
      st[tp] = a[i]
      tp += 1
      w[tp] = 1
    else:
      t = 0
      while (tp and st[tp - 1] >= a[i]):
        t += w[tp]
        ans = max(ans, t * st[tp - 1])
        tp -= 1
      st[tp] = a[i]
      tp += 1
      w[tp] = t + 1
  t = 0
  # print(n, tp, st, w)
  while (tp and st[tp - 1] >= 0):
    t += w[tp]
    ans = max(ans, t * st[tp - 1])
    tp -= 1
  print(ans)
