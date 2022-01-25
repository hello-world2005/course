def Dfs(pos, ans):
  if (len(pre[pos]) == 0):
    # print(ans)
    if (len(ans) == maxn):
      # print(ans)
      anss.append(tuple(ans))
    return
  for i in pre[pos]:
    ans.append(i)
    Dfs(i, ans)
    ans.pop()

a = list(map(int, input().split()))
m = int(input())
n = len(a)
dp = [1 for i in range(n)]
pre = [[] for i in range(n)]
maxn = 0
for i in range(n):
  for j in range(i):
    if (a[j] < a[i]):
      dp[i] = max(dp[i], dp[j] + 1)
      # pre[i].append(j)
  maxn = max(maxn, dp[i])
  for j in range(i):
    if (a[j] < a[i] and dp[j] + 1 == dp[i]):
      pre[i].append(j)
print(maxn)
anss = []
for i in range(n - 1, -1, -1):
  p = i
  ans = [i]
  Dfs(p, ans)
anss.sort(reverse = True)
ansss = []
for i in anss:
  ansss.append(list(i))
for i in range(len(ansss)):
  ansss[i].reverse()
for i in range(min(len(ansss), m)):
  for j in range(len(ansss[i])):
    print(ansss[i][j] + 1, end = ' ' if j != maxn - 1 else '\n')
if (len(ansss) < m):
  print("Can't find more")
