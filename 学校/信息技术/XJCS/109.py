m = int(input())
n = int(input())
a = list(map(int, input().split()))
q = list(range(n))
st, ed = 0, 0
ans = 0
for i in a:
  flag = False
  for j in range(st, ed):
    if (q[j] == i):
      flag = True
      break
  if (flag): continue
  ans += 1
  q[ed] = i
  if (ed - st < m):
    ed += 1
    continue
  ed += 1
  st += 1
print(ans)