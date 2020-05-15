#include <cstdio>

const int N = 1e4 + 10;
const int MOD = 1e9 + 7;

int a[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    a[i] = i;
  while (m--) {
    int opt, l, r, k;
    scanf("%d%d%d", &opt, &l, &r);
    if (opt == 1) {
      scanf("%d", &k);
      for (int i = l; i <= r; ++i)
        (a[i] += k) %= MOD;
    } else if (opt == 2) {
      scanf("%d", &k);
      for (int i = l; i <= r; ++i)
        a[i] = 1ll * a[i] * k % MOD;
    } else if (opt == 3) {
      scanf("%d", &k);
      for (int i = l; i <= r; ++l)
        a[i] = k;
    } else if (opt == 4) {
      for (int i = l; i <= r; ++i)
        a[i] = a[i + 1];
    } else {
      int ans = 0;
      for (int i = l; i <= r; ++i)
        (ans += a[i]) %= MOD;
      printf("%d\n", ans);
    }
  }
  return 0;
}
