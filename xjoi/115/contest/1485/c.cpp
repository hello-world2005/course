#include <algorithm>
#include <cstdio>
#include <queue>

#define int long long

const int N = 1010;

int n, m;
int a[N], sum[N];
int dp[N][N];
int sqr[N];

double Slope(int x, int y, int i) {
  if (sum[y] == sum[x])
    return -1e8;
  return 1.0 *
         ((dp[y][i - 1] - dp[x][i - 1]) + sum[y] * sum[y] - sum[x] * sum[x]) /
         (sum[y] - sum[x]);
}

signed main() {
  scanf("%lld%lld", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]);
  for (int i = 1; i <= n; ++i) {
    sum[i] = sum[i - 1] + a[i];
    sqr[i] = sqr[i - 1] + a[i] * a[i];
    dp[i][0] = (sum[i] - sum[0]) * (sum[i] - sum[0]);
  }
#ifdef DEBUG
  int x, y;
  while (scanf("%lld%lld", &x, &y) == 2 && x && y)
    printf("%lld\n", (sum[y] - sum[x]) * (sum[y] - sum[x]) -
                         (sqr[y] - sqr[x]));
#endif
  for (int i = 1; i <= m; ++i) {
    std::deque<int> q;
    q.push_back(0);
    for (int j = 1; j <= n; ++j) {
      while (q.size() >= 2 && Slope(q[0], q[1], i) <= 2.0 * sum[j])
        q.pop_front();
      dp[j][i] = dp[q[0]][i - 1] + (sum[j] - sum[q[0]]) * (sum[j] - sum[q[0]]);
      while (q.size() >= 2 && Slope(q[q.size() - 2], q[q.size() - 1], i) >=
                                  Slope(q[q.size() - 1], j, i))
        q.pop_back();
      q.push_back(j);
    }
  }
  printf("%lld\n", (dp[n][m] - sqr[n]) / 2);
  return 0;
}