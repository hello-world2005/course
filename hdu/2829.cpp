#include <cstdio>

#define int long long

const int N = 1010;

int a[N];
int s1[N], s2[N];
int dp[N][N], p[N][N];

int Sqr(int x) {
  return x * x;
}

int Cost(int l, int r) {
  return (Sqr(s1[r] - s1[l - 1]) - s2[r] + s2[l - 1]) / 2;
}

signed main() {
  int n, m;
  while (scanf("%lld%lld", &n, &m) == 2 && n && m) {
    ++m;
    for (int i = 1; i <= n; ++i)
      scanf("%lld", &a[i]), p[1][i] = 1;
    for (int i = 1; i <= n; ++i)
      s1[i] = s1[i - 1] + a[i], s2[i] = s2[i - 1] + Sqr(a[i]);
    // printf("%lld %lld\n", Cost(1, 1), Cost(2, 4));
    for (int i = 1; i <= n; ++i)
      dp[1][i] = Cost(1, i);
    for (int i = 2; i <= m; ++i) {
      p[i][n + 1] = n - 1;
      for (int j = n; j >= i; --j) {
        int minn = 0x3f3f3f3f, pos = 0;
        for (int k = p[i - 1][j]; k <= p[i][j + 1]; ++k)
          if (dp[i - 1][k] + Cost(k + 1, j) < minn)
            minn = dp[i - 1][k] + Cost(k + 1, j), pos = k;
        dp[i][j] = minn, p[i][j] = pos;
      }
    }
    printf("%lld\n", dp[m][n]);
  }
  return 0;
}
