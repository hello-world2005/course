#include <algorithm>
#include <cstdio>

#define int ing
#define ing long long

const int N = 1e5 + 10;

int n, m;
int a[N], b[N];

signed main() {
  scanf("%lld%lld", &n, &m);
  int minn = 0x3f3f3f3f, maxn = 0;
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]), maxn = std::max(maxn, a[i]);
  for (int i = 1; i <= m; ++i)
    scanf("%lld", &b[i]), minn = std::min(minn, b[i]);
  std::sort(a + 1, a + n + 1);
  std::sort(b + 1, b + m + 1);
  if (maxn > minn) {
    printf("-1\n");
    return 0;
  }
  int ans = 0;
  for (int i = 1; i < n; ++i)
    ans += a[i];
  ans *= m;
  if (a[n] != b[1])
    ans += a[n] - a[n - 1];
  for (int i = 1; i <= m; ++i)
    ans += b[i];
  printf("%lld\n", ans);
  return 0;
}
