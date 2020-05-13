#include <cstdio>

#define int long long

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int n, cnt = 0, ans = 0, k = 1;
    scanf("%lld", &n);
    int _n = n;
    _n /= 10;
    while (_n) {
      _n /= 10;
      ans += 9;
      k = k * 10 + 1;
    }
    for (int i = 1; i <= 9; ++i)
      if (k * i <= n)
        ++ans;
    printf("%lld\n", ans);
  }
  return 0;
}
