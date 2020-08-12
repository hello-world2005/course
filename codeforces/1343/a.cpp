#include <cstdio>

#define int long long

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int n;
    scanf("%lld", &n);
    for (int i = 2; i <= 30; ++i)
      if (n % ((1ll << i) - 1) == 0) {
        printf("%lld\n", n / ((1ll << i) - 1));
        break;
      }
  }
  return 0;
}
