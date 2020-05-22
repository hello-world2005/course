#include <cstdio>

#define int long long

const int N = 5e4 + 10;
const int MOD = 1e6 + 3;

int a[N];

signed main() {
  int n, m;
  scanf("%lld%lld", &n, &m);
  for (int i = 1; i <= n; ++i)
    a[i] = i;
  while (m--) {
    int opt, l, r, k;
    scanf("%lld%lld%lld", &opt, &l, &r);
    if (opt == 1) {
      scanf("%lld", &k);
      for (int i = l; i <= r; ++i)
        (a[i] += k) %= MOD;
    } else if (opt == 2) {
      scanf("%lld", &k);
      for (int i = l; i <= r; ++i)
        a[i] = 1ll * a[i] * k % MOD;
    } else if (opt == 3) {
      scanf("%lld", &k);
      k %= MOD;
      for (int i = l; i <= r; ++i)
        a[i] = k;
    } else if (opt == 4) {
      for (int i = l; i <= r; ++i)
        a[i] = a[i + 1];
    } else if (opt == 5) {
      for (int i = r; i >= l; --i)
        a[i] = a[i - 1];
    } else {
      int ans = 0;
      for (int i = l; i <= r; ++i)
        (ans += a[i]) %= MOD;
      printf("%lld\n", (ans + MOD) % MOD);
    }
    // for (int i = 1; i <= n; ++i)
    //   printf("%lld ", a[i]);
    // printf("\n");
  }
  return 0;
}
