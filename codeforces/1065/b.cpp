#include <algorithm>
#include <cstdio>

#define int long long

signed main() {
  int n, m;
  scanf("%lld%lld", &n, &m);
  printf("%lld ", std::max(0ll, n - m * 2));
  int ans = 0;
  if (m == 0) {
    printf("%lld\n", n);
    return 0;
  }
  for (int i = 1; i <= n; ++i)
    if (1ll * i * (i - 1) / 2 >= m) {
      ans = i;
      break;
    }
  printf("%lld\n", n - ans);
  return 0;
}
