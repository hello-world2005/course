#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

#define int long long

const int N = 1010;
const int M = N * N;

int n, m;
struct Edge {
  int v, w, nxt;

  Edge()
      : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt)
      : v(_v), w(_w), nxt(_nxt) {}
} e[M];
int head[N], edge_cnt = 1;
int sum[N];

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int idx[20][M];

const int INF = 1e16;

int cur[N], dep[N];

bool Bfs(int s, int t) {
  memcpy(cur, head, sizeof(cur));
  memset(dep, 0, sizeof(dep));
  std::queue<int> q;
  q.push(s), dep[s] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].w;
      if (!w || dep[v])
        continue;
      q.push(v), dep[v] = dep[u] + 1;
    }
  }
  return dep[t] > 0;
}

int Dfs(int u, int val, int t) {
  if (u == t)
    return val;
  int res = 0;
  for (int& i = cur[u]; i; i = e[i].nxt) {
    int v = e[i].v, w = e[i].w;
    if (!w || dep[v] != dep[u] + 1)
      continue;
    int now = Dfs(v, std::min(val, w), t);
    e[i].w -= now, e[i ^ 1].w += now;
    val -= now, res += now;
  }
  if (res == 0)
    dep[u] = 0;
  return res;
}

int Dinic(int s, int t) {
  int res = 0;
  while (Bfs(s, t)) {
    res += Dfs(s, INF, t);
    // printf("%lld\n", res);
  }
  return res;
}

bool vis[M];

void Dfs(int u) {
  vis[u] = true;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v, w = e[i].w;
    if (w && !vis[v])
      Dfs(v);
  }
}

signed main() {
  scanf("%lld%lld", &n, &m);
  int cnt = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      idx[i][j] = ++cnt;
  int s = cnt + 1, t = s + 1;
  for (int i = 1, u, v, w; i <= m; ++i) {
    scanf("%lld%lld%lld", &u, &v, &w);
    sum[u] += w, sum[v] -= w;
    for (int j = 0; j < n; ++j)
      AddEdge(idx[v][j], idx[u][j + 1], INF), AddEdge(idx[u][j + 1], idx[v][j], 0);
  }
  for (int i = 1; i <= n; ++i) {
    AddEdge(s, idx[i][0], INF), AddEdge(idx[i][0], s, 0);
    AddEdge(idx[i][n], t, INF), AddEdge(t, idx[i][n], 0);
    for (int j = 0; j < n; ++j)
      AddEdge(idx[i][j], idx[i][j + 1], sum[i] * j + 3e9), AddEdge(idx[i][j + 1], idx[i][j], 0);
  }
  Dinic(s, t);
  // printf("!\n");
  Dfs(s);
  for (int i = 1; i <= n; ++i) {
    int ans = 0;
    for (int j = 0; j <= n; ++j)
      if (vis[idx[i][j]])
        ans = j;
    printf("%lld ", ans);
  }
  return 0;
}
