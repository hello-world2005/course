#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 110;
const int INF = 0x3f3f3f3f;

int n;
struct Edge {
  int v, w, nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[N * N << 1];
int head[N], edge_cnt = 1;

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int d[N];

void AddEdge(int u, int v, int l, int r) {
  AddEdge(u, v, r - l);
  AddEdge(v, u, 0);
  d[u] -= l;
  d[v] += l;
}

bool Bfs(int s, int t) {
  memset(d, 0, sizeof(d));
  std::queue<int> q;
  q.push(s);
  d[s] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].w;
      if (d[v] || !w)
        continue;
      q.push(v);
      d[v] = d[u] + 1;
      if (v == t)
        return true;
    }
  }
  return false;
}

int Dfs(int u, int flow, int t) {
  if (u == t)
    return flow;
  int res = flow;
  for (int i = head[u]; i && res; i = e[i].nxt) {
    int v = e[i].v, w = e[i].w;
    if (d[v] != d[u] + 1 || !w)
      continue;
    int now = Dfs(v, std::min(res, w), t);
    if (!now) {
      d[v] = 0;
    } else {
      e[i].w -= now;
      e[i ^ 1].w += now;
      res -= now;
    }
  }
  return flow - res;
}

int main() {
  scanf("%d", &n);
  int s = n + 1, t = n + 2;
  for (int u = 1, m; u <= n; ++u) {
    AddEdge(s, u, 0, INF);
    AddEdge(u, t, 0, INF);
    scanf("%d", &m);
    for (int i = 1, v; i <= m; ++i) {
      scanf("%d", &v);
      AddEdge(u, v, 1, INF);
    }
  }
  int S = s + 2, T = t + 2;
  for (int i = 1; i <= t; ++i) {
    if (d[i] > 0)
      AddEdge(S, i, d[i]), AddEdge(i, S, 0);
    else if (d[i] < 0)
      AddEdge(i, T, -d[i]), AddEdge(T, i, 0);
  }
  while (Bfs(S, T)) {
    Dfs(S, INF, T);
  }
  AddEdge(t, s, 0, INF);
  while (Bfs(S, T)) {
    Dfs(S, INF, T);
  }
  printf("%d\n", e[edge_cnt].w);
  return 0;
}
