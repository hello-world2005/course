#include <cstdio>

const int MOD = 1e9 + 7;

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % MOD)
    if (b & 1)
      res = 1ll * res * a % MOD;
  return res;
}

int main() {
  int n;
  scanf("%d", &n);
  int fac = 1, pow2 = 1;
  for (int i = 2; i <= n; ++i)
    fac = 1ll * fac * i % MOD, pow2 = 1ll * pow2 * 2 % MOD;
  printf("%d\n", ((fac - pow2) % MOD + MOD )% MOD);
}
