#include <cstdio>

#define int long long

const int K = 5010;
const int MOD = 1e9 + 7;

int dp[K][K], ans;

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = a * a % MOD)
    if (b & 1)
      res = res * a % MOD;
  return res;
}

signed main() {
  int n, m = 2, k;
  scanf("%lld%lld", &n, &k);
  dp[0][0] = 1;
  for (int i = 1; i <= k; ++i)
    for (int j = 1; j <= i; ++j)
      dp[i][j] = (dp[i - 1][j - 1] * (n + 1 - j) + dp[i - 1][j] * j) % MOD;
  for (int i = 1; i <= k; ++i)
    ans += dp[k][i] * FastPow(FastPow(m, MOD - 2), i) % MOD, ans %= MOD;
  printf("%lld\n", (ans *= FastPow(2, n)) %= MOD);
  return 0;
}
