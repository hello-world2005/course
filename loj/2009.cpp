// u -> u 的两棵子树 -> fa -> fa 的另一棵子树 ...

#include <algorithm>
#include <cstdio>
#include <cstring>

#define int long long

const int N = 2e5 + 10;
const int K = 20;
const int INF = 0x3f3f3f3f3f3f3f3f;

int a[N], b[N];
int dis[N][K];
int dp1[N][K], dp2[N][K];

int Pat(int u, int k) {
  if ((1 << (k - 1)) <= u)
    return u >> k;
  return -1;
}

int Another(int u, int k) {
  return (u >> (k - 1)) ^ 1;
}

signed main() {
  int n;
  scanf("%lld", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]);
  for (int i = 2; i <= n; ++i)
    scanf("%lld", &b[i]), dis[i][1] = b[i];
  for (int i = 2; i <= n; ++i)
    for (int j = 2; ~Pat(i, j); ++j)
      dis[i][j] = dis[Pat(i, 1)][j - 1] + dis[i][1];
  // memset(dp1, 0x3f, sizeof(dp1));
  // memset(dp2, 0x3f, sizeof(dp2));
  for (int i = n; i >= 1; --i)
    for (int j = 1; ~Pat(i, j); ++j) {
      dp1[i][j] = dp2[i][j] = INF;
      if ((i << 1) > n) {
        dp1[i][j] = dis[i][j] * a[Pat(i, j)];
        dp2[i][j] = (dis[i][j] + dis[Another(i, j)][1]) * a[Another(i, j)];
      } else if ((i << 1 | 1) > n) {
        dp1[i][j] = dp1[i << 1][j + 1] + dis[i << 1][1] * a[i << 1];
        dp2[i][j] = dp2[i << 1][j + 1] + dis[i << 1][1] * a[i << 1];
      } else {
        dp1[i][j] = std::min(dp2[i << 1][1] + dp1[i << 1 | 1][j + 1] +
                                 dis[i << 1][1] * a[i << 1],
                             dp2[i << 1 | 1][1] + dp1[i << 1][j + 1] +
                                 dis[i << 1 | 1][1] * a[i << 1 | 1]);
        dp2[i][j] = std::min(dp2[i << 1][1] + dp2[i << 1 | 1][j + 1] +
                                 dis[i << 1][1] * a[i << 1],
                             dp2[i << 1 | 1][1] + dp2[i << 1][j + 1] +
                                 dis[i << 1 | 1][1] * a[i << 1 | 1]);
      }
    }
#ifdef DEBUG
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= 3; ++j)
      printf("%lld ", dp1[i][j]);
    printf("\n");
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= 3; ++j)
      printf("%lld ", dp2[i][j]);
    printf("\n");
  }
#endif
  int ans = INF;
  for (int i = 1; i <= n; ++i) {
    int res = dp1[i][1];
    for (int j = Pat(i, 1), qwq = i; ~j; qwq = j, j = Pat(j, 1)) {
      if (Another(qwq, 1) <= n)
        res += dis[(Another(qwq, 1))][1] * a[Another(qwq, 1)] +
               dp1[Another(qwq, 1)][2];
      else
        res += dis[j][1] * a[Pat(j, 1)];
    }
    ans = std::min(ans, res);
  }
  printf("%lld\n", ans);
  return 0;
}
