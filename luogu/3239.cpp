#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 230;

int d[N];
double p[N], f[N];
double dp[N][N];

double FastPow(double a, int b) {
  double res = 1;
  for (; b; b >>= 1, a = a * a)
    if (b & 1)
      res = res * a;
  return res;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
      scanf("%lf%d", &p[i], &d[i]);
    memset(dp, 0, sizeof(dp));
    memset(f, 0, sizeof(f));
    dp[1][0] = FastPow(1 - p[1], m);
    dp[1][1] = f[1] = 1 - FastPow(1 - p[1], m);
    for (int i = 2; i <= n; ++i)
      for (int j = 0; j <= std::min(i, m); ++j) {
        if (j)
          dp[i][j] += dp[i - 1][j - 1] * (1 - FastPow(1 - p[i], m - j + 1));
        if (i != j)
          dp[i][j] += dp[i - 1][j] * FastPow(1 - p[i], m - j);
      }
    for (int i = 2; i <= n; ++i)
      for (int j = 0; j <= std::min(i - 1, m); ++j)
        f[i] += dp[i - 1][j] * (1 - FastPow(1 - p[i], m - j));
    double ans = 0;
    for (int i = 1; i <= n; ++i)
      ans += d[i] * f[i];
    printf("%.10lf\n", ans);
  }
  return 0;
}
