#include <cstdio>

const int N = 2e5 + 10;
const int MOD = 998244353;

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % MOD)
    if (b & 1)
      res = 1ll *res * a % MOD;
  return res;
}

int Inv(int a, int b) {
  // a / b
  return int(1ll * a * FastPow(b, MOD - 2) % MOD);
}

int p[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &p[i]);
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    ans = 100ll * (ans + 1) % MOD * Inv(1, p[i]) % MOD;
  printf("%d\n", ans);
  return 0;
}
