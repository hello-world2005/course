#include <algorithm>
#include <cstdio>

#define int long long

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int p, q, ans = 0;
    scanf("%lld%lld", &p, &q);
    for (int i = 2; i * i <= q; ++i)
      if (q % i == 0) {
        int now = 1, cnt = 0;
        while (q % i == 0)
          q /= i, ++cnt, now *= i;
        int _ = p;
        while (_ % now == 0)
          _ /= i;
        ans = std::max(ans, _);
      }
    if (q > 1) {
      int _ = p;
      while (_ % q == 0)
        _ /= q;
      ans = std::max(ans, _);
    }
    printf("%lld\n", ans);
  }
}
