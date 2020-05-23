#include <algorithm>
#include <cstdio>

const int N = 110;
const int M = 10;

int n, m;
int a[N];
int dp[3][1 << M][1 << M];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i)
    for (int j = 0, u; j < m; ++j)
      scanf("%d", &u), a[i] <<= 1, a[i] |= u;
  for (int i = 0; i < (1 << m); ++i)
    if (!(i & a[0] || (i & (i << 1)) || (i & (i << 2))))
      dp[0][0][i] = __builtin_popcount(i);
  for (int i = 0; i < (1 << m); ++i)
    for (int j = 0; j < (1 << m); ++j)
      if (!(i & j || i & a[0] || j & a[1] || (i & (i << 1)) || (i & (i << 2)) ||
            (j & (j << 1)) || (j & (j << 2))))
        dp[1][i][j] = __builtin_popcount(i) + __builtin_popcount(j);
  for (int i = 2; i < n; i++)
    for (int j = 0; j < (1 << m); ++j) {
      if (j & a[i - 1] || (j & (j << 1)) || (j & (j << 2)))
        continue;
      for (int k = 0; k < (1 << m); ++k) {
        if (k & a[i] || j & k || (k & (k << 1)) || (k & (k << 2)))
          continue;
        for (int l = 0; l < (1 << m); ++l) {
          if (l & j || l & k || l & a[i - 2] || (l & (l << 1)) ||
              (l & (l << 2)))
            continue;
          dp[i % 3][j][k] = std::max(
              dp[i % 3][j][k], dp[(i - 1) % 3][l][j] + __builtin_popcount(k));
        }
      }
    }
  int ans = 0;
  for (int i = 0; i < (1 << m); ++i)
    for (int j = 0; j < (1 << m); ++j)
      ans = std::max(ans, dp[(n - 1) % 3][i][j]);
  printf("%d\n", ans);
  return 0;
}
