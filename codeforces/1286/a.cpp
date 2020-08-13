#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 110;

int a[N], b[N];
int dp[N][N][N][2];  // i 位 用了 j 个奇数 k 个偶数 当前是奇数/偶数

int main() {
  int n;
  scanf("%d", &n);
  int cnt1 = 0, cnt2 = 0;
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), a[i] == 0 ? a[i] = -1 : a[i] &= 1;
  cnt1 = (n + 1) / 2, cnt2 = n / 2;
  memset(dp, 0x3f, sizeof(dp));
  dp[0][0][0][0] = dp[0][0][0][1] = 0;
  for (int i = 1; i <= n; ++i)
    if (a[i] == -1) {
      for (int j = 1; j <= i; ++j) {
        int k = i - j;
        dp[i][j][k][1] = std::min(dp[i - 1][j - 1][k][1], dp[i - 1][j - 1][k][0] + 1);
      }
      for (int j = 0; j < i; ++j) {
        int k = i - j;
        dp[i][j][k][0] = std::min(dp[i - 1][j][k - 1][0], dp[i - 1][j][k - 1][1] + 1);
      }
    } else {
      if (a[i])
        for (int j = 1; j <= i; ++j) {
          int k = i - j;
          dp[i][j][k][1] = std::min(dp[i - 1][j - 1][k][1], dp[i - 1][j - 1][k][0] + 1);
        }
      else
        for (int j = 0; j < i; ++j) {
          int k = i - j;
          dp[i][j][k][0] = std::min(dp[i - 1][j][k - 1][0], dp[i - 1][j][k - 1][1] + 1);
        }
    }
  printf("%d\n", std::min(dp[n][cnt1][cnt2][0], dp[n][cnt1][cnt2][1]));
  return 0;
}
