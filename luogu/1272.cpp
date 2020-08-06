#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 160;

struct Edge {
  int v, nxt;

  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

int deg[N], dp[N][N], sze[N];

void Dfs(int u, int fa) {
  dp[u][1] = deg[u];
  sze[u] = 1;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    Dfs(v, u);
    sze[u] += sze[v];
    for (int x = sze[u]; x >= 1; --x)
      for (int y = 0; y <= std::min(x, sze[v]); ++y)
        dp[u][x] = std::min(dp[u][x], dp[u][x - y] + dp[v][y] - 1);
  }
}

bool leaf[N];

int main() {
  int n, p;
  scanf("%d%d", &n, &p);
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v);
    ++deg[u], leaf[v] = true;
  }
  memset(dp, 0x3f, sizeof(dp));
  int rt = 0;
  for (int i = 1; i <= n; ++i)
    if (!leaf[i])
      rt = i;
  Dfs(rt, 0);
  int ans = dp[rt][p];
  for (int i = 1; i <= n; ++i)
    if (dp[i][p] != dp[0][0] && i != rt)
      ans = std::min(ans, dp[i][p] + 1);
  printf("%d\n", ans);
  return 0;
}
