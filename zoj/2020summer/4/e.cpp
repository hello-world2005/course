#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>

#define int long long

const int N = 1010;
const int P = 10010;

int a[N], b[N], c[N];
int q[P];
int dp[N][P];

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int n, p;
    scanf("%lld%lld", &n, &p);
    for (int i = 1; i <= n; ++i)
      scanf("%lld", &a[i]);
    for (int i = 1; i <= n; ++i)
      scanf("%lld", &b[i]);
    for (int i = 1; i <= n; ++i)
      scanf("%lld", &c[i]);
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; ++i) {
      int h = 1, t = 0;
      for (int j = a[i]; j <= b[i]; ++j)
        dp[i][j] = c[i];
      dp[i][0] = 0;
      for (int j = 1; j <= p; ++j) {
        while (h <= t && q[h] < j - b[i])
          ++h;
        dp[i][j] = std::min(dp[i][j], dp[i - 1][j]);
        if (h <= t && j - b[i] <= q[h] && j - a[i] >= q[h])
          dp[i][j] = std::min(dp[i][j], dp[i - 1][q[h]] + c[i]);
        if (j - a[i] + 1 >= 0) {
          while (h <= t && dp[i - 1][j - a[i] + 1] <= dp[i - 1][q[t]])
            --t;
          q[++t] = j - a[i] + 1;
        }
      }
    }
    printf("%lld\n", dp[n][p] == dp[0][0]? -1 : dp[n][p]);
  }
  return 0;
}
