#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 2e4 + 10;
const int M = 1e6 + 10;
const int INF = 0x3f3f3f3f;

struct Edge {
  int v, w, nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[M];
int head[N], edge_cnt = 1, cur[N];

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int dep[N];

bool Bfs(int s, int t) {
  for (int i = 1; i <= t; ++i)
    cur[i] = head[i];
  std::queue<int> q;
  memset(dep, 0, sizeof(dep));
  q.push(s);
  dep[s] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].w;
      if (!w || dep[v])
        continue;
      q.push(v);
      dep[v] = dep[u] + 1;
    }
  }
  return dep[t] > 0;
}

int Dfs(int u, int val, int t) {
  if (u == t)
    return val;
  int res = 0;
  for (int& i = cur[u]; i && val; i = e[i].nxt) {
    int v = e[i].v, w = e[i].w;
    if (!w || dep[v] != dep[u] + 1)
      continue;
    int now = Dfs(v, std::min(val, w), t);
    e[i].w -= now;
    e[i ^ 1].w += now;
    val -= now;
    res += now;
  }
  if (res == 0)
    dep[u] = 0;
  return res;
}

int Dinic(int s, int t) {
  int res = 0;
  while (Bfs(s, t))
    res += Dfs(s, INF, t);
  return res;
}

int col[N], v[N];

int main() {
  int n, m, g, sum = 0;
  scanf("%d%d%d", &n, &m, &g);
  int s = n + m + 1, t = s + 1;
  for (int i = 1; i <= n; ++i)
    scanf("%d", &col[i]);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &v[i]);
    if (!col[i])
      AddEdge(s, i, v[i]), AddEdge(i, s, 0);
    else
      AddEdge(i, t, v[i]), AddEdge(t, i, 0);
  }
  for (int i = 1, c, w, k; i <= m; ++i) {
    scanf("%d%d%d", &c, &w, &k);
    sum += w;
    if (c) {
      for (int j = 1, p; j <= k; ++j) {
        scanf("%d", &p);
        AddEdge(p, i + n, INF);
        AddEdge(i + n, p, 0);
      }
      int q;
      scanf("%d", &q);
      if (!q)
        AddEdge(i + n, t, w), AddEdge(t, i + n, 0);
      else
        AddEdge(i + n, t, g + w), AddEdge(t, i + n, 0);
    } else {
      for (int j = 1, p; j <= k; ++j) {
        scanf("%d", &p);
        AddEdge(i + n, p, INF);
        AddEdge(p, i + n, 0);
      }
      int q;
      scanf("%d", &q);
      if (!q)
        AddEdge(s, i + n, w), AddEdge(i + n, s, 0);
      else
        AddEdge(s, i + n, g + w), AddEdge(i + n, s, 0);
    }
  }
  int res = Dinic(s, t);
  printf("%d\n", sum - res);
  return 0;
}
