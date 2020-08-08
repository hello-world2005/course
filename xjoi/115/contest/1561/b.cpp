#include <algorithm>
#include <cstdio>

const int N = 1e5 + 10;
const int MOD = 1e9 + 7;

int a[N];
int dp[N];

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % MOD)
    if (b & 1)
      res = 1ll * res * a % MOD;
  return res;
}

int Inv(int a) { return FastPow(a, MOD - 2); }

int main() {
  int n, sum = 0, maxn = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), sum += a[i], maxn = std::max(maxn, a[i]);
  dp[0] = 0, dp[1] = 1ll * (sum - 1) * (sum - 1) % MOD * Inv(sum) % MOD;
  for (int i = 1; i <= maxn; ++i)
    dp[i + 1] = (2ll * dp[i] - dp[i - 1] - 1ll * (sum - 1) * Inv(sum - i) % MOD) % MOD;
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    ans = (ans + dp[a[i]]) % MOD;
  printf("%d\n", (ans + MOD) % MOD);
  return 0;
}
