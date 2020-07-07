#include <algorithm>
#include <cstdio>

#define int long long

const int N = 210;

int a[N][N];

signed main() {
  int n, p;
  scanf("%lld%lld", &n, &p);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      scanf("%lld", &a[i][j]);
  int ans = 1, f = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      int x = i, y = j;
      while (a[y][i]) {
        int t = a[x][i] / a[y][i];
        for (int k = i; k <= n; ++k)
          a[x][k] = (a[x][k] - a[y][k] * t % p) % p;
        std::swap(x, y);
      }
      if (x != i) {
        for (int k = 1; k <= n; ++k)
          std::swap(a[i][k], a[j][k]);
        f = -f;
      }
    }
    ans = ans * a[i][i] % p;
  }
  ans = (ans * f + p) % p;
  printf("%lld\n", ans);
  return 0;
}
