#include <algorithm>
#include <cstdio>

const int N = 1e4 + 10;
const int M = 5e3 + 10;

int a[N];
int dp[N][M], p[N][M];

int Sqr(int x) {
  return x * x;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]), p[i][1] = 1;
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i)
      dp[i][1] = Sqr(a[i] - a[1]);
    for (int i = 2; i <= m; ++i) {
      p[n + 1][i] = n - 1;
      for (int j = n; j >= i; --j) {
        int minn = 0x3f3f3f3f, pos = 0;
        for (int k = p[j][i - 1]; k <= p[j + 1][i]; ++k)
          if (dp[k][i - 1] + Sqr(a[j] - a[k + 1]) < minn)
            minn = dp[k][i - 1] + Sqr(a[j] - a[k + 1]), pos = k;
        dp[j][i] = minn, p[j][i] = pos;
      }
    }
    printf("Case %d: %d\n", cas, dp[n][m]);
  }
  return 0;
}
