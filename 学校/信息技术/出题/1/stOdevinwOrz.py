import queue

N = int(5e4 + 10)
M = int(5e5 + 10)
INF = int(1e18)

class Edge:
  def __init__(self) -> None:
    self.v, self.w, self.nxt = 0, 0, 0
  def __init__(self, v, w, nxt) -> None:
    self.v, self.w, self.nxt = v, w, nxt

head = [0 for i in range(N)]
e = [(0, 0, 0) for i in range(M)]
edge_cnt = 1

def AddEdge(u, v, w):
  global edge_cnt
  edge_cnt += 1
  e[edge_cnt] = Edge(v, w, head[u])
  head[u] = edge_cnt

d = [0 for i in range(N)]

def AddEdge1(u, v, l, r):
  AddEdge(u, v, r - l)
  AddEdge(v, u, 0)
  d[u] -= l
  d[v] += l

r = [0 for i in range(N)]

def Bfs(s, t):
  # global r
  # global d
  # r = head
  for i in range(N):
    d[i] = 0
  q = queue.SimpleQueue()
  q.put(s)
  d[s] = 1
  while (not q.empty()):
    u = q.get()
    # print(u)
    i = head[u]
    while (i):
      v = e[i].v
      w = e[i].w
      if (d[v] != 0 or w == 0):
        i = e[i].nxt
        continue
      q.put(v)
      d[v] = d[u] + 1
      i = e[i].nxt
  return d[t] > 0

def Dfs(u, f, t):
  if (u == t):
    return f
  q = f
  # i = r[u]
  i = head[u]
  while (i != 0 and q != 0):
    v = e[i].v
    w = e[i].w
    # r[u] = i
    if (d[v] != d[u] + 1 or w == 0):
      i = e[i].nxt
      continue
    now = Dfs(v, min(q, w), t)
    if (now == 0):
      d[v] = 0
    else:
      e[i].w -= now
      e[i ^ 1].w += now
      q -= now
    i = e[i].nxt
  return f - q

def Dinic(s, t):
  while (Bfs(s, t)):
    Dfs(s, INF, t)

n, m, s, t = map(int, input().split())
for i in range(m):
  u, v, l, r = map(int, input().split())
  AddEdge1(u, v, l, r)
S = n + 1
T = n + 2
for i in range(1, n + 1):
  if (d[i] > 0):
    AddEdge(S, i, d[i])
    AddEdge(i, S, 0)
  elif (d[i] < 0):
    AddEdge(i, T, -d[i])
    AddEdge(T, i, 0)
Dinic(S, T)
AddEdge1(t, s, 0, INF)
Dinic(S, T)
ans = True
i = head[S]
while (i):
  if (e[i].w > 0):
    ans = False
    break
  i = e[i].nxt
if (ans):
  print(e[edge_cnt].w)
else:
  print('please go home to sleep')
