li = list(map(int, input().split(' ')))
a, n = li[0], li[1]

q1, q2 = list(range(n)), list(range(n))
tl1, tl2 = -1, -1
hd1, hd2 = 0, 0
tot = 1
while tot < n:
  x = 2 * a + 1
  y = 3 * a + 1
  tl1 += 1
  q1[tl1] = x
  tl2 += 1
  q2[tl2] = y
  if q1[hd1] < q2[hd2]:
    a = q1[hd1]
    hd1 += 1
  elif q1[hd1] > q2[hd2]:
    a = q2[hd2]
    hd2 += 1
  else:
    a = q1[hd1]
    hd1 += 1
    hd2 += 1
  tot += 1
print(a)
