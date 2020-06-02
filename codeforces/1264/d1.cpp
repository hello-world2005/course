#include <cstdio>
#include <cstring>

#define int long long

const int N = 2010;
const int MOD = 998244353;

int n;
char s[N];
int a[N], sum[N];
int dp[N][N];
int pow2[N];

signed main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (int i = 1; i <= n; ++i) {
    if (s[i] == '(')
      a[i] = 1;
    if (s[i] == ')')
      a[i] = -1;
    sum[i] = sum[i - 1] + (!a[i]);
  }
  pow2[0] = 1;
  for (int i = 1; i < N; ++i)
    pow2[i] = (pow2[i - 1] << 1) % MOD;
  for (int i = 2; i <= n; ++i)
    for (int j = 1; j <= n - i + 1; ++j) {
      int t = i + j - 1;
      if (a[t] != -1)
        dp[j][t] = (dp[j][t] + dp[j][t - 1]) % MOD;
      if (a[j] != 1)
        dp[j][t] = (dp[j][t] + dp[j + 1][t] -
                    (a[t] == -1 ? 0 : dp[j + 1][t - 1]) + MOD) %
                   MOD;
      if (a[j] != -1)
        dp[j][t] = (dp[j][t] + (a[t] == 1 ? 0
                                          : (pow2[(sum[t - 1] - sum[j])]) +
                                                dp[j + 1][t - 1])) %
                   MOD;
    }
  printf("%lld\n", dp[1][n]);
  return 0;
}
