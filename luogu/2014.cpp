#include <algorithm>
#include <cstdio>

const int N = 310;

int dp[N][N];
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
int w[N];
int n, m;

void Dfs(int u, int fa) {
  dp[u][1] = w[u];
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    Dfs(v, u);
    for (int x = m + 1; x >= 1; --x)
      for (int y = 0; y < x; ++y)
        dp[u][x] = std::max(dp[u][x], dp[v][y] + dp[u][x - y]);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, fa; i <= n; ++i) {
    scanf("%d%d", &fa, &w[i]);
    AddEdge(fa, i), AddEdge(i, fa);
  }
  Dfs(0, 0);
  printf("%d\n", dp[0][m + 1]);
}
