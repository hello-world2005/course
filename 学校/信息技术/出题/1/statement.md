## 题目描述

zyy 有一份代码```stOdevinwOrz.py```，但他觉得太长了，于是找到 lhx 让他帮忙压行。

lhx 会熟练使用互联网~~查找题解~~查找 Python 的奇特语法和各种函数，所以你写成什么样都可以。但是 lhx 又不希望更改后的代码得到 0 分的好成绩，所以他想让你尽量不改变代码原本的逻辑。（你一定要改 lhx 也不会拦你，但他会对 0 分的成绩感到很生气）。

[```stOdevinwOrz.py```](https://paste.ubuntu.com/p/fFGwhfhZ7W/) 在这里，你需要提交你修改过后的代码。

或者见下。

```python
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
e = [Edge(0, 0, 0) for i in range(M)]
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

def Bfs(s, t):
  for i in range(N):
    d[i] = 0
  q = queue.SimpleQueue()
  q.put(s)
  d[s] = 1
  while (not q.empty()):
    u = q.get()
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
  i = head[u]
  while (i != 0 and q != 0):
    v = e[i].v
    w = e[i].w
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
  print('emm')
```

题目得分将与你代码长度有关。

## 输入格式

你只要照搬或修改 ```stOdevinwOrz.py``` 的输入部分代码就好了。

## 输出格式

你只要照搬或修改 ```stOdevinwOrz.py``` 的输出部分代码就好了。

## 样例

作为一道类答案提交题你不需要样例。

## 数据范围与提示

反正原本的代码能拿到满分，你能不能让 lhx 满意就看你的造化了。

本题开启 Special Judge
- 你的代码长度 $\le$ lhx 希望的代码长度，100pts；
- 你的代码长度 $\le$ lhx 希望的代码长度 $*\ 1.05$，80pts；
- 你的代码长度 $\le$ lhx 希望的代码长度 $*\ 1.1$，50pts；
- 你的代码长度 $\le$ lhx 希望的代码长度 $*\ 1.2$，20pts；
- 你的代码再长 lhx 就要不开心了，但是鉴于你做出的努力，lhx 决定给你 5pts 的~~好成绩~~；
- 你的代码不能给出和原先一样的结果，那 lhx 会非常生气，你将获得 0pts 和 lhx 的蔑视。

~~不要试图理解代码要实现的东西~~
