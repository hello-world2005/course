#include <cstdio>

#define int long long

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int s, a, b, c;
    scanf("%lld%lld%lld%lld", &s, &a, &b, &c);
    printf("%lld\n", (s / c) / a * b + s / c);
  }
  return 0;
}
