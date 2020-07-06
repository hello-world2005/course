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
  int s, t;
  scanf("%d%d%d%d", &n, &m, &s, &t);
  for (int i = 1, u, v, l, r; i <= m; ++i) {
    scanf("%d%d%d%d", &u, &v, &l, &r);
    AddEdge(u, v, l, r);
    k[i] = l;
  }
  int S = n + 1, T = n + 2;
  AddEdge(t, s, INF);
  AddEdge(s, t, 0);
  int sum = 0;
  for (int i = 1; i <= n; ++i) {
    if (d[i] > 0)
      AddEdge(S, i, d[i]), AddEdge(i, S, 0), sum += d[i];
    else if (d[i] < 0)
      AddEdge(i, T, -d[i]), AddEdge(T, i, 0);
  }
  Dinic(S, T);
  bool full = true;
  for (int i = head[S]; i; i = e[i].nxt)
    if (e[i].w > 0) {
      full = false;
      break;
    }
  if (full) {
    printf("%d\n", Dinic(s, t));
  } else {
    printf("please go home to sleep\n");
  }
  return 0;
}
