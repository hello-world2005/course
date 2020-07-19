#include <cstdio>

#define int long long

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int l, r, m;
    scanf("%lld%lld%lld", &l, &r, &m);
    int b, c;
    for (int a = l; a <= r; ++a) {
      int n = m / a;
      int d = m - a * n;
      // d = b - c
      if (d < 0)
        b = l, c = l + d;
      else
        b = r, c = r - d;
      if (n > 0 && l <= a && a <= r && l <= b && b <= r && l <= c && c <= r &&
          m == a * n + b - c) {
        printf("%lld %lld %lld\n", a, b, c);
        break;
      }
      --n;
      d = m - a * n;
      // d = b - c
      if (d < 0)
        b = l, c = l + d;
      else
        b = r, c = r - d;
      if (n > 0 && l <= a && a <= r && l <= b && b <= r && l <= c && c <= r &&
          m == a * n + b - c) {
        printf("%lld %lld %lld\n", a, b, c);
        break;
      }
      n += 2;
      d = m - a * n;
      // printf("%lld %lld\n", n, d);
      // d = b - c
      if (d < 0)
        b = l, c = l - d;
      else
        b = r, c = r - d;
      if (n > 0 && l <= a && a <= r && l <= b && b <= r && l <= c && c <= r &&
          m == a * n + b - c) {
        printf("%lld %lld %lld\n", a, b, c);
        break;
      }
    }
  }
  return 0;
}
