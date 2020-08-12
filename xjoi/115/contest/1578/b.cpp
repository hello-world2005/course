#include <cstdio>

#define int long long

const int MOD = 1e9 + 7;

int n;
int dp[32][32][2];
int a[32];
int pow2[32];

int solve(int n, int pre, bool ismax) {
  if (n == -1)
    return 1;
  if (dp[n][pre][ismax])
    return dp[n][pre][ismax];
  int res = 0;
  if (ismax) {
    if (a[n])
      res = solve(n - 1, pre + 1, ismax);
    res = (res + solve(n - 1, pre, a[n] ^ 1) * pow2[pre]) % MOD;
    if (a[n] && pre)
      res = (res + solve(n - 1, pre, a[n]) * pow2[pre]) % MOD;
  } else {
    res = (solve(n - 1, pre + 1, ismax) + solve(n - 1, pre, false) * pow2[pre]) % MOD;
    if (pre)
      res = (res + solve(n - 1, pre, false) * pow2[pre]) % MOD;
  }
  return dp[n][pre][ismax] = res;
}

signed main() {
  scanf("%lld", &n);
  int x = n;
  for (int i = 0; i < 32; ++i)
    a[i] = x & 1, x >>= 1;
  pow2[0] = pow2[1] = 1;
  for (int i = 2; i < 32; ++i)
    pow2[i] = pow2[i - 1] << 1;
  printf("%lld", solve(31, 0, true));
  return 0;
}
