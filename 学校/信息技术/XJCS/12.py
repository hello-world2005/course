s = input().split(' ')
poly = {}
for i in s:
  poly.setdefault(int(i[-1]), 0)
  poly[int(i[-1])] += int(i[0 : -1])
ans = []
for i in poly:
  ans.append(str(poly[i]) + str(i))
for i in range(len(ans)):
  if i != len(ans) - 1:
    print(ans[i], end = ' ')
  else:
    print(ans[i])