#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 3010;

struct Edge {
  int v, w, nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int n, m;
int a[N];
int sze[N], dp[N][N];

void Dfs(int u, int fa) {
  if (a[u])
    return dp[u][1] = a[u], sze[u] = 1, void();
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v, w = e[i].w;
    if (v == fa)
      continue;
    Dfs(v, u);
    sze[u] += sze[v];
    for (int x = m; x >= 1; --x)
      for (int y = 0; y <= std::min(sze[v], x); ++y)
        dp[u][x] = std::max(dp[u][x], dp[u][x - y] + dp[v][y] - w);
  }
}

int main() {
  memset(dp, -0x3f, sizeof(dp));
  scanf("%d%d", &n, &m);
  for (int u = 1, k; u <= n - m; ++u) {
    scanf("%d", &k);
    for (int j = 1, v, w; j <= k; ++j) {
      scanf("%d%d", &v, &w);
      AddEdge(u, v, w), AddEdge(v, u, w);
    }
  }
  for (int i = n - m + 1; i <= n; ++i)
    scanf("%d", &a[i]);
  for (int i = 1; i <= n; ++i)
    dp[i][0] = 0;
  Dfs(1, 0);
  for (int i = m; i >= 1; --i)
    if (dp[1][i] >= 0)
      return printf("%d\n", i), 0;
  return 0;
}
