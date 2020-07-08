#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 310;

int n, m, k;
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

int dp[N][N][2], cpy[N][2];

void Dfs(int u, int fa) {
  dp[u][0][0] = dp[u][1][1] = 0;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v, w = e[i].w;
    if (v == fa)
      continue;
    Dfs(v, u);
    for (int j = 0; j <= k; ++j)
      cpy[j][0] = dp[u][j][0], cpy[j][1] = dp[u][j][1];
    // memcpy(cpy, dp[u], sizeof(dp[u]));
    memset(dp[u], 0x3f, sizeof(dp[u]));
    for (int j = 0; j <= k; ++j)
      for (int l = 0; l <= j; ++l) {
        dp[u][j][0] = std::min(
            dp[u][j][0], std::min(dp[v][l][0] + cpy[j - l][0] + (m == 2) * w,
                                  dp[v][l][1] + cpy[j - l][0]));
        dp[u][j][1] =
            std::min(dp[u][j][1], std::min(dp[v][l][0] + cpy[j - l][1],
                                           dp[v][l][1] + cpy[j - l][1] + w));
      }
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  if (m + k - 1 > n) {
    printf("-1\n");
    return 0;
  }
  for (int i = 2, u, v, w; i <= n; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    AddEdge(u, v, w);
    AddEdge(v, u, w);
  }
  memset(dp, 0x3f, sizeof(dp));
  Dfs(1, 0);
  printf("%d\n", dp[1][k][1]);
  return 0;
}
