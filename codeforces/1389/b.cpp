#include <algorithm>
#include <cstdio>

const int N = 1e5 + 10;

int a[N], sum[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, k, z;
    scanf("%d%d%d", &n, &k, &z);
    ++k;
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    if (n == 2) {
      printf("%d\n", a[1] + a[2]);
      continue;
    }
    for (int i = 1; i <= n; ++i)
      sum[i] = sum[i - 1] + a[i];
    int ans = 0, maxn = 0;
    for (int i = 2; i <= std::min(n, k); ++i) {
      maxn = std::max(maxn, a[i] + a[i - 1]);
      if (k - i <= 2 * z) {
        if ((k - i) & 1)
          ans = std::max(ans, sum[i] + (k - i) / 2 * maxn + a[i - 1]);
        else
          ans = std::max(ans, sum[i] + (k - i) / 2 * maxn);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
