// 一些显然的想法
// 叶子节点肯定要选
// 如果没有覆盖当前点的肯定要在相邻节点放置
// dp[u][k][f1][f2]  // u k 0/1 0/1
// 覆盖 选

#include <algorithm>
#include <cstdio>
#include <cstring>

// #define int long long
typedef long long ll;

const int N = 1e5 + 10;
const int K = 110;
const int MOD = 1e9 + 7;

int n, k;
int dp[N][K][2][2];
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

int sze[N];
int _dp[K][2][2];

void Dfs(int u, int fa) {
  sze[u] = 1;
  dp[u][0][0][0] = dp[u][1][1][0] = 1;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    Dfs(v, u);
    for (int x = 0; x <= std::min(sze[u], k); ++x)
      _dp[x][0][0] = dp[u][x][0][0], _dp[x][0][1] = dp[u][x][0][1],
      _dp[x][1][0] = dp[u][x][1][0], _dp[x][1][1] = dp[u][x][1][1],
      memset(dp[u][x], 0, sizeof(dp[u][x]));
    for (int x = 0; x <= std::min(sze[u], k); ++x)
      for (int y = 0; y <= std::min(sze[v], k - x); ++y) {
        // printf("%d %d %d %d\n", u, v, x, y);
        dp[u][x + y][0][0] =
            (dp[u][x + y][0][0] + 1ll * _dp[x][0][0] * dp[v][y][0][1]) % MOD;
        dp[u][x + y][0][1] =
            (dp[u][x + y][0][1] + 1ll * _dp[x][0][0] * dp[v][y][1][1] +
             1ll * _dp[x][0][1] * dp[v][y][1][1] +
             1ll * _dp[x][0][1] * dp[v][y][0][1]) %
            MOD;
        dp[u][x + y][1][0] =
            (dp[u][x + y][1][0] + 1ll * _dp[x][1][0] * dp[v][y][0][0] +
             1ll * _dp[x][1][0] * dp[v][y][0][1]) %
            MOD;
        dp[u][x + y][1][1] =
            (dp[u][x + y][1][1] + 1ll * _dp[x][1][1] * dp[v][y][0][0] +
             1ll * _dp[x][1][1] * dp[v][y][0][1] +
             1ll * _dp[x][1][1] * dp[v][y][1][0] +
             1ll * _dp[x][1][1] * dp[v][y][1][1] +
             1ll * _dp[x][1][0] * dp[v][y][1][0] +
             1ll * _dp[x][1][0] * dp[v][y][1][1]) %
            MOD;
      }
    sze[u] += sze[v];
  }
}

signed main() {
  scanf("%d%d", &n, &k);
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v), AddEdge(v, u);
  }
  Dfs(1, 0);
  printf("%d\n", (dp[1][k][0][1] + dp[1][k][1][1]) % MOD);
  return 0;
}
