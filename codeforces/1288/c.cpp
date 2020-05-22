#include <cstdio>

const int MOD = 1e9 + 7;
const int N = 1010;
const int M = 20;

int n, m;
int dp[M][N][N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    dp[1][i][i] = 1;
    for (int j = 1; j <= m; ++j) {
      if (j != 1)
        for (int k = i; k <= n; ++k)
          dp[j][i][k] = dp[j - 1][i][k];
      for (int k = i; k <= n; ++k)
        dp[j][i][k] = (dp[j][i][k] + dp[j][i][k - 1]) % MOD;
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = i; j <= n; ++j)
      ans = (ans + 1ll * dp[m][n - i + 1][n] % MOD * dp[m][j][n]) % MOD;
  printf("%d\n", ans);
  return 0;
}
