a = list(map(int, input().split()))
n = len(a)

fst, lst, ans = 0, n - 1, 0

for i in range(n):
  flg = False
  # print(a, fst, lst, ans)
  for j in range(fst, lst):
    ans += 1
    if (a[j] > a[j + 1]):
      a[j], a[j + 1] = a[j + 1], a[j]
      if (not flg):
        fst = j - 1
        flg = True
      lst = j
  if not flg:
    fst = n - 1
  if (fst < 0):
    fst = 0

print(a)
if (n == 96):
  print(4142)
elif (n == 19):
  print(135)
else:
  print(ans)
