#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 110;
const int M = 2e3 + 10;
const int MOD = 998244353;

int a[N][M], sum[N][M];
int dp[N][N << 1];
int qwq[N][N];

int main() {
  int n, m, ans = 0;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      scanf("%d", &a[i][j]);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      (sum[i][0] += a[i][j]) %= MOD;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      sum[i][j] = (sum[i][0] - a[i][j]) % MOD;
  for (int i = 1; i <= m; ++i) {
    memset(dp, 0, sizeof(dp));
    dp[0][n] = 1;
    for (int j = 1; j <= n; ++j)
      for (int k = n - j; k <= n + j; ++k)
        dp[j][k] = (dp[j - 1][k] + 1ll * dp[j - 1][k - 1] * a[j][i] % MOD + 1ll * dp[j - 1][k + 1] * sum[j][i] % MOD) % MOD;
    for (int j = 1; j <= n; ++j)
      (ans += dp[n][n + j]) %= MOD;
  }
  qwq[0][0] = 1;
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j <= n; ++j)
      qwq[i][j] = (qwq[i - 1][j] + (j > 0 ? 1ll * qwq[i - 1][j - 1] * sum[i][0] % MOD : 0)) % MOD;
  for (int i = 1; i <= n; ++i)
    (ans -= qwq[n][i]) %= MOD;
  (ans += MOD) %= MOD;
  printf("%lld\n", 1ll * ans * (MOD - 1) % MOD);
  return 0;
}
