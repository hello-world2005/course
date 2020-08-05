#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 110;
const int K = 60;

int n, k;
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

int a[N];
int dep[N], sze[N];
int dp[N][N][K][2];
// $dp_{i, j, k, 0/1} $i$ 子树选 $k$ 个祖先 $j$ 选了 $i$ 节点选/不选$
int vis[N], idx;

void Dfs(int u) {
  sze[u] = 1, vis[++idx] = u;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v, w = e[i].w;
    dep[v] = dep[u] + w;
    Dfs(v);
    sze[u] += sze[v];
    for (int x = 1; x <= idx; ++x)
      for (int y = k; y >= 0; --y) {
        dp[u][vis[x]][y][0] += dp[v][vis[x]][0][0];
        dp[u][vis[x]][y][1] += dp[v][u][0][0];
        for (int z = 0; z <= y; ++z) {
          dp[u][vis[x]][y][0] = std::min(dp[u][vis[x]][y][0], dp[u][vis[x]][y - z][0] + dp[v][vis[x]][z][0]);
          dp[u][vis[x]][y][1] = std::min(dp[u][vis[x]][y][1], dp[u][vis[x]][y - z][1] + dp[v][u][z][0]);
        }
      }
  }
  for (int x = 1; x <= idx; ++x)
    for (int y = 0; y <= k; ++y)
      if (!y)
        dp[u][vis[x]][y][0] += a[u] * (dep[u] - dep[vis[x]]);
      else
        dp[u][vis[x]][y][0] = std::min(dp[u][vis[x]][y][0] + a[u] * (dep[u] - dep[vis[x]]), dp[u][vis[x]][y - 1][1]);
  --idx;
}

int main() {
  scanf("%d%d", &n, &k);
  ++n;
  for (int u = 2, v, w; u <= n; ++u) {
    scanf("%d%d%d", &a[u], &v, &w);
    ++v;
    AddEdge(v, u, w);
  }
  Dfs(1);
  // for (int i = 1; i <= n; ++i)
  //   for (int j = 1; j <= n; ++j)
  //     for (int x = 0; x <= k; ++x)
  //       printf("%d %d %d: %d %d\n", i, j, x, dp[i][j][x][0], dp[i][j][x][1]);
  printf("%d\n", dp[1][1][k][0]);
  return 0;
}
