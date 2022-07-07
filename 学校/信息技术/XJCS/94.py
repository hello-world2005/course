a = list(map(int, input().split()))
i = 0

def Check(a, n):
  _ = n
  b = [0 for i in range(10)]
  while (_):
    b[_ % 10] += 1
    _ //= 10
  for i in range(10):
    if (a[i] < b[i]): return False
  return True

def Modify(a, n):
  _ = n
  b = []
  while (_):
    b.append(_ % 10)
    _ //= 10
  for i in b:
    a[i] -= 1

while (Check(a, i + 1)):
  i += 1
  Modify(a, i)
print(i)
