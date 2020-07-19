#include <algorithm>
#include <cstdio>

// #define int long long

const int N = 510;
const int K = 20;
const int V = 1e5 + 10;

int x[V], y[V], v[K];
int dp[V][K];

signed main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1, k = 0; i <= n * m; ++i) {
    scanf("%d", &k);
    ++x[k];
  }
  for (int i = 1, k = 0; i <= n; ++i) {
    scanf("%d", &k);
    ++y[k];
  }
  for (int i = 1; i <= m; ++i)
    scanf("%d", &v[i]);
  // printf("%d\n", x[513]);
  int ans = 0;
  for (int i = 1; i <= 100000; ++i) {
    if (!x[i] || !y[i])
      continue;
    if (x[i] / y[i] >= m) {
      ans += 1ll * y[i] * v[m];
      // printf("> %d\n", i);
      continue;
    }
    // printf(">> %d %d %d\n", i, x[i], y[i]);
    for (int j = 1; j <= y[i]; ++j)
      for (int k = 1; k <= m; ++k)
        dp[j][k] = 0;
    for (int j = 1; j <= x[i]; ++j) {
      for (int k = y[i]; k >= 1; --k) {
        int maxn = 0;
        for (int l = m; l >= 2; --l)
          if (dp[k][l - 1])
            dp[k][l] = std::max(dp[k][l], dp[k][l - 1] + v[l] - v[l - 1]);
        for (int l = 1; l <= m; ++l)
          maxn = std::max(maxn, dp[k - 1][l]);
        dp[k][1] = maxn + v[1];
      }
    }
    int maxn = 0;
    for (int j = 1; j <= y[i]; ++j)
      for (int k = 1; k <= m; ++k)
        maxn = std::max(maxn, dp[j][k]);
    // printf("%d\n", maxn);
    ans += maxn;
  }
  printf("%d\n", ans);
  return 0;
}
