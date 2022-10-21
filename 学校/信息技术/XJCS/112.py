s = input().split(',')
edge = [[] for i in range(len(s))]
fa = 0
qwq = []
for i in s:
  if (i != 'None'): qwq.append(int(i))
k = 0
for i in s:
  if (i == 'None'): fa = qwq[k]; k += 1
  else: edge[fa].append(int(i))
# print(edge)
max_dep = 0
max_wid = 0
wid = [0 for i in range(len(s))]
def Dfs(u, dep):
  wid[dep] += 1
  global max_dep
  max_dep = max_dep if (dep < max_dep) else dep
  for v in edge[u]: Dfs(v, dep + 1)
Dfs(0, 0)
max_wid = max(wid)
print(max_dep, max_wid, sep = '\n')

