import io
import os
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

n = int(input())
st, tp = [0 for i in range(n + 10)], 0
ans = 0
for i in range(n):
  a = int(input())
  while (tp and st[tp - 1] <= a):
    tp -= 1
  ans += tp
  st[tp] = a
  tp += 1
print(ans)
