#include <algorithm>
#include <cstdio>

const int N = 2e3 + 10;
const int MOD = 1e9 + 9;

int a[N], b[N];
int dp[N][N];
int fac[N], c[N][N];

void Init(int n) {
  fac[0] = c[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = 1ll * fac[i - 1] * i % MOD;
    c[i][0] = 1;
    for (int j = 1; j <= i; ++j)
      c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
  }
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  if ((n - k) & 1) {
    printf("0\n");
    return 0;
  }
  Init(n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &b[i]);
  k = (n + k) >> 1;
  std::sort(a + 1, a + n + 1), std::sort(b + 1, b + n + 1);
  for (int i = 0; i <= n; ++i)
    dp[i][0] = 1;
  for (int i = 1, p = 0; i <= n; ++i) {
    while (p < n && b[p + 1] < a[i])
      ++p;
    for (int j = 1; j <= n; ++j)
      dp[i][j] = (dp[i - 1][j] + 1ll * dp[i - 1][j - 1] * (p - j + 1)) % MOD;
  }
  int ans = 0;
  for (int i = k; i <= n; ++i)
    if ((i - k) & 1)
      ans = (ans - 1ll * c[i][k] * fac[n - i] % MOD * dp[n][i] % MOD) % MOD;
    else
      ans = (ans + 1ll * c[i][k] * fac[n - i] % MOD * dp[n][i] % MOD) % MOD;
  printf("%d\n", (ans + MOD) % MOD);
  return 0;
}
