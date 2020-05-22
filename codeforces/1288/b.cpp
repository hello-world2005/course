// ab + a + b = (a + 1)(b + 1) - 1

#include <cstdio>

#define int long long

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int a, b, ans = 0;
    scanf("%lld%lld", &a, &b);
    for (int i = 10;; i *= 10) {
      if (i - 1 > b)
        break;
      ans += a;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
