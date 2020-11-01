#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 210;

int a[N];
int dp[2 * N][N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    std::sort(a + 1, a + n + 1);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= 2 * n; ++i) {
      dp[i][0] = 0;
      for (int j = 1; j <= std::min(i, n); ++j) {
        dp[i][j] = std::min(dp[i - 1][j], dp[i - 1][j - 1] + abs(i - a[j]));
      }
      ans = std::min(ans, dp[i][n]);
    }
    printf("%d\n", ans);
  }
  return 0;
}
