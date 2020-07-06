#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 410;
const int M = 20210;
const int INF = 0x3f3f3f3f;

int n, m;
struct Edge {
  int v, w, nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[M << 1];
int head[N], edge_cnt = 1;
int d[N];

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

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
    }
  }
  return d[t] > 0;
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

int Dinic(int s, int t) {
  int res = 0;
  while (Bfs(s, t))
    res += Dfs(s, INF, t);
  return res;
}

int ans[M], k[M];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v, l, r; i <= m; ++i) {
    scanf("%d%d%d%d", &u, &v, &l, &r);
    AddEdge(u, v, l, r);
    k[i] = l;
  }
  int s = n + 1, t = n + 2;
  for (int i = 1; i <= n; ++i) {
    if (d[i] > 0)
      AddEdge(s, i, d[i]), AddEdge(i, s, 0);
    else if (d[i] < 0)
      AddEdge(i, t, -d[i]), AddEdge(t, i, 0);
  }
  Dinic(s, t);
  bool full = true;
  for (int i = head[s]; i; i = e[i].nxt)
    if (e[i].w > 0) {
      full = false;
      break;
    }
  if (full) {
    printf("YES\n");
    for (int i = 2; i <= edge_cnt; i += 2)
      ans[(i >> 1)] = e[i ^ 1].w;
    for (int i = 1; i <= m; ++i)
      printf("%d\n", ans[i] + k[i]);
  }
  else {
    printf("NO\n");
  }
  return 0;
}
