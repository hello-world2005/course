a = list(map(int, input().split()))
cnt = [0 for i in range(len(a))]
maxn = max(a)
tot = 1
for i in range(maxn):
  for j in range(len(a)):
    if (a[j] == 0): continue
    cnt[j] = tot
    a[j] -= 1
    tot += 1
for i in cnt:
  print(i, end = ' ')
print()