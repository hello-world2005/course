#include <cstdio>

const int MOD = 19260817;

int Gcd(int a, int b) {
  while (b ^= a ^= b ^= a %= b)
    ;
  return a;
}

int main() {
  int fac = 1, pow = 1, n;
  scanf("%d", &n);
  for (int i = 1; i <= n - 2; ++i)
    fac = (1ll * fac * i) % MOD, pow = (2ll * pow) % MOD;
  fac = (1ll * fac * (n - 1)) % MOD;
  int gcd = Gcd(fac, pow);
  printf("%d %d\n", pow / gcd, fac / gcd);
  return 0;
}
