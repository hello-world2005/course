#include <cstdio>
#include <cmath>

#define int long long

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int c, h, t;
    scanf("%lld%lld%lld", &h, &c, &t);
    if (h + c >= 2 * t) {
      printf("2\n");
    } else {
      int delta1 = h - t, delta2 = 2 * t - c - h;
      int k = 2 * (delta1 / delta2) + 1;
      int ans1 = abs(k / 2 * c + (k + 1) / 2 * h - t * k);
      int ans2 = abs((k + 2) / 2 * c + (k + 3) / 2 * h - t * (k + 2));
      // printf("%lld\n", k);
      printf("%lld\n", ans1 * (k + 2) <= ans2 * k ? k : k + 2);
    }
  }
  return 0;
}
