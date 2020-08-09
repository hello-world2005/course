#include <cstdio>
#include <cstring>
#include <cmath>

const int N = 1010;

struct Point {
  int x, y;

  Point() : x(0), y(0) {}
  Point(int _x, int _y) : x(_x), y(_y) {}
} a[N];
int dp[N][N], p[N][N];

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; ++i)
      scanf("%d%d", &a[i].x, &a[i].y), dp[i][i] = 0, p[i][i] = i;
    for (int l = 2; l <= n; ++l) {
      p[n - l + 2][n] = n;
      for (int i = n - l + 1; i >= 1; --i) {
        int j = i + l - 1;
        for (int k = p[i][j - 1]; k <= p[i + 1][j] && k <= j; ++k)
          if (dp[i][k] + dp[k + 1][j] + abs(a[k + 1].x - a[i].x) + abs(a[k].y - a[j].y) < dp[i][j])
            dp[i][j] = dp[i][k] + dp[k + 1][j] + abs(a[k + 1].x - a[i].x) + abs(a[k].y - a[j].y), p[i][j] = k;
      }
    }
    printf("%d\n", dp[1][n]);
  }
  return 0;
}
