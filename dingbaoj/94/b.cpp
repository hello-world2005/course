#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e4 + 10;
const int M = 6e4 + 10;

int n, m;
struct Edge {
  int v, nxt;

  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} e[M << 1];
int head[N], edge_cnt = 1;

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

int dp[N][2][2], g[2][2];
int dfn[N], idx, fa[N], tp[N], bt[N];

void Dfs(int u, int fa) {
  dfn[u] = ++idx, ::fa[u] = fa;
  bool flag = false;
  for (int i = head[u]; i; i = e[i].nxt)
    if (e[i].v != fa && dfn[e[i].v])
      flag = true;
  dp[u][1][flag] = 1;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    if (!dfn[v]) {
      Dfs(v, u);
      memset(g, 0, sizeof(g));
      for (int j = 0; j <= 1; ++j)
        for (int k = 0; k <= 1; ++k)
          for (int x = 0; x <= 1; ++x)
            for (int y = 0; y <= 1; ++y) {
              if ((j && x) || (j && y && tp[v]))
                continue;
              g[j][k || (y && !tp[v])] =
                  std::max(g[j][k || (y && !tp[v])], dp[u][j][k] + dp[v][x][y]);
            }
      for (int j = 0; j <= 1; ++j)
        for (int k = 0; k <= 1; ++k)
          dp[u][j][k] = g[j][k];
    } else if (dfn[v] < dfn[u]) {
      int x = u;
      while (::fa[x] != v)
        x = ::fa[x];
      tp[x] = 1;
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v), AddEdge(v, u);
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    if (!dfn[i]) {
      Dfs(i, 0);
      int res = 0;
      for (int j = 0; j <= 1; ++j)
        for (int k = 0; k <= 1; ++k)
          res = std::max(res, dp[i][j][k]);
      ans += res;
    }
  printf("%d\n", ans);
  return 0;
}
