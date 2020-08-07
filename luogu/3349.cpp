#include <cstdio>
#include <cstring>
#include <vector>

#define int long long

const int N = 20;

int n, m;
std::vector<int> g[N], h[N];
bool vis[N];
int dp[N][N];

void Dfs(int u, int fa) {
  for (int i = 0; i < n; ++i)
    dp[u][i] = 1;
  for (auto v : h[u]) {
    if (v == fa)
      continue;
    Dfs(v, u);
    for (int i = 0; i < n; ++i) {
      int sum = 0;
      for (int j = 0; j < n; ++j)
        sum += dp[v][j] * (g[i][j] * vis[i] * vis[j]);
      dp[u][i] *= sum;
    }
  }
}

signed main() {
  scanf("%lld%lld", &n, &m);
  for (int i = 0; i < n; ++i)
    g[i].resize(n);
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%lld%lld", &u, &v), --u, --v;
    g[u][v] = g[v][u] = 1;
  }
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%lld%lld", &u, &v), --u, --v;
    h[u].push_back(v), h[v].push_back(u);
  }
  int ans = 0;
  for (int mask = 1; mask < (1 << n); ++mask) {
    int cnt = n;
    memset(vis, false, sizeof(vis));
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; ++i)
      if (mask >> i & 1)
        vis[i] = true, --cnt;
    Dfs(0, 0);
    int res = 0;
    for (int i = 0; i < n; ++i)
      res += dp[0][i];
    ans += ((cnt & 1) ? -1 : 1) * res;
    // printf("%lld %lld\n", mask, res);
  }
  printf("%lld\n", ans);
  return 0;
}
