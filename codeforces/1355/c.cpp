#include <algorithm>
#include <cstdio>

#define int long long

signed main() {
  int a, b, c, d;
  scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
  int ans = 0;
  for (int i = a; i <= b; ++i) {
    // x + y > z
    int y1 = b, y2 = c;
    // int z1 = c, z2 = std::min(d, x + y2);
    // if (d == z2) {
    //   int s = d - c - 1, e = std::max(0ll, x + y1 - c);
    //   printf("1%lld %lld\n", s, e);
    //   ans += (s + e) * (e - s) / 2;
    // } else {
    //   int s = x + y2 - c - 1, e = std::max(0ll, x + y1 - c);
    //   printf("2%lld %lld\n", s, e);
    //   ans += (s + e) * (e - s) / 2;
    // }
    int x = std::max(b, c - i + 1) + i - c;
    int y = std::min(c, d - i + 1) + i - c;
    ans += ((x + y) * std::max(y - x + 1, 0ll)) / 2;
    ans += std::min(c - std::min(c, d - i + 1), c - b + 1) * (d - c + 1);
  }
  printf("%lld\n", ans);
  return 0;
}
