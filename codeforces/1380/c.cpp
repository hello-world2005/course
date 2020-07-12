#include <algorithm>
#include <cstdio>

#define int long long

const int N = 1e5 + 10;

int a[N];

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int n, k;
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; ++i)
      scanf("%lld", &a[i]);
    std::sort(a + 1, a + n + 1,
              [&](const int lhs, const int rhs) { return lhs > rhs; });
    // int l = 0, r = n, ans;
    // while (l <= r) {
    //   int mid = (l + r) >> 1;
    //   if (Check())
    // }
    int ans = 0;
    for (int i = 1, cnt = 0; i <= n; ++i) {
      ++cnt;
      if (a[i] * cnt >= k)
        cnt = 0, ++ans;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
