n = int(input())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
minn = int(1e9)
m = n
n *= 2
ccnt, dcnt = 0, 0
for j in range(m):
  for k in range(m):
    if (a[j] < b[k]): ccnt += 1
    if (a[j] > b[k]): dcnt += 1
for i in range(m):
  _a = a[i:] + a[:i]
  acnt, bcnt = 0, 0
  for j in range(m):
    for k in range(j):
      if (_a[j] > _a[k]): acnt += 1
  _b = b[i:] + b[:i]
  for j in range(m):
    for k in range(j):
      if (_b[j] > _b[k]): bcnt += 1
  minn = min(minn, acnt + bcnt, acnt + bcnt)
print(minn + min(ccnt, dcnt))
