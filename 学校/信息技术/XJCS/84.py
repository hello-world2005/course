n = int(input())
a = list(map(int, input().split()))
m = sum(a)
MOD = 998244353
def F(a, b):
  res = 1
  for i in range(a, b):
    res = (res * i) % MOD
  return res
print(F(1, m - n + 1) * F(m - n + 2, m + 1) % MOD)