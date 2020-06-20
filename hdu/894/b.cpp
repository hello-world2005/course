#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>

#define int long long

const int MOD = 1e9 + 7;

int Gcd(int a, int b) {
  return b == 0 ? a : Gcd(b, a % b);
}

int Mul(int a, int b) {
  a %= MOD;
  int res = 0;
  while (b) {
    if (b & 1)
      res = (res + a) % MOD;
    a = (a + a) % MOD;
    b >>= 1;
  }
  return res;
}

int FastPow(int a, int b) {
  a %= MOD;
  int res = 1;
  for (; b; b >>= 1, a = a * a % MOD)
    if (b & 1)
      res = res * a % MOD;
  return res;
}

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int n, mul = 1;
    int a[20];
    scanf("%lld", &n);
    // for (int i = 1, x; i <= n; ++i) {
    // scanf("%lld", &x);
    // gcd = Gcd(x % MOD, lcm);
    // mul = Mul(x, mul);
    // lcm = lcm * FastPow(gcd, MOD - 2) % MOD * (x % MOD) % MOD;
    // printf("%lld %lld\n", gcd, lcm);
    // }
    // printf("%lld\n", gcd);
    // printf("%lld\n", lcm);
    // printf("%lld\n", 1000000000000000000ll % MOD);
    for (int i = 0; i < n; ++i) {
      scanf("%lld", &a[i]);
      mul = Mul(mul, a[i]);
    }
    for (int i = 1; i < (1 << n); ++i) {
      int gcd = 0, cnt = 0;
      for (int j = 0; j < n; ++j)
        if (i >> j & 1)
          gcd = Gcd(a[j], gcd), ++cnt;
      if (cnt <= 1)
        continue;
      gcd %= MOD;
      if (!(cnt & 1))
        mul = mul * FastPow(gcd, MOD - 2) % MOD;
      else
        mul = mul * gcd % MOD;
    }
    printf("%lld\n", mul);
  }
  return 0;
}

// 1
// 4
// 1000000000000000000 1000000000000000000 1000000000000000000
// 1000000000000000000
