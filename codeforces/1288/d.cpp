#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 3e5 + 10;
const int M = 10;

int n, m;
int a[N][M];
int dp[N], p[1 << M];

bool Check(int mid, int& x, int& y) {
  memset(dp, 0, sizeof(dp));
  memset(p, 0, sizeof(p));
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < m; ++j)
      if (a[i][j] >= mid)
        dp[i] |= (1 << j);
    p[dp[i]] = i;
  }
  // for (int i = 0; i < (1 << m); ++i)
  //   printf("%d ", p[i]);
  // printf("\n");
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j < (1 << m); ++j)
      if ((dp[i] | j) == (1 << m) - 1 && p[j]) {
        x = i, y = p[j];
        return true;
      }
  return false;
}

int main() {
  scanf("%d%d", &n, &m);
  int l = 0, r = 0, ans, ansx, ansy;
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j < m; ++j)
      scanf("%d", &a[i][j]), r = std::max(r, a[i][j]);
  while (l <= r) {
    int mid = (l + r) >> 1, x, y;
    if (Check(mid, x, y)) {
      // printf("%d %d %d\n", mid, x, y);
      l = mid + 1, ans = mid;
      ansx = x, ansy = y;
    } else {
      r = mid - 1;
    }
  }
  printf("%d %d\n", ansx, ansy);
}
