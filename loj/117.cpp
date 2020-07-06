#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

#define int long long

const int N = 5e4 + 10;
const int M = 5e5 + 10;
const int INF = 1e16;

int n, m;
struct Edge {
  int v, w, nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[M];
int head[N], edge_cnt = 1;

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int d[N];
int cur[N];

void AddEdge(int u, int v, int l, int cur) {
  AddEdge(u, v, cur - l);
  AddEdge(v, u, 0);
  d[u] -= l;
  d[v] += l;
}

bool Bfs(int s, int t) {
  for (int i = 1; i <= n + 2; ++i)
    d[i] = 0, cur[i] = head[i];
  std::queue<int> q;
  q.push(s);
  d[s] = 1;
  while (!q.empty()) {
    int u = q.front();
    // printf("%d ", u);
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
  for (int i = cur[u]; i && res; i = e[i].nxt) {
    cur[u] = i;
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

void Dinic(int s, int t) {
  while (Bfs(s, t))
    Dfs(s, INF, t);
}

signed main() {
  // freopen("117.in", "r", stdin);
  int s, t;
  scanf("%lld%lld%lld%lld", &n, &m, &s, &t);
  for (int i = 1, u, v, l, cur; i <= m; ++i) {
    scanf("%lld%lld%lld%lld", &u, &v, &l, &cur);
    AddEdge(u, v, l, cur);
  }
  int S = n + 1, T = n + 2;
  for (int i = 1; i <= n; ++i) {
    if (d[i] > 0)
      AddEdge(S, i, d[i]), AddEdge(i, S, 0);
    else if (d[i] < 0)
      AddEdge(i, T, -d[i]), AddEdge(T, i, 0);
  }
  Dinic(S, T);
  AddEdge(t, s, 0, INF);
  // printf("qwq\n");
  // system("pause");
  Dinic(S, T);
  bool full = true;
  for (int i = head[S]; i; i = e[i].nxt)
    if (e[i].w > 0) {
      full = false;
      break;
    }
  if (full) {
    printf("%lld\n", e[edge_cnt].w);
  } else {
    printf("please go home to sleep\n");
  }
  return 0;
}
