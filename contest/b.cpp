#include <cstdio>

typedef long long ll;

const int MOD = 998244353;

ll FastPow(ll a, ll b) {
  ll res = 1;
  for (; b; b >>= 1, a = a * a % MOD)
    if (b & 1)
      res = res * a % MOD;
  return res;
}

int main() {
  ll n;
  scanf("%lld", &n);
  printf("%lld\n", ((FastPow(4, n) % MOD - (n + 1) % MOD * FastPow(2, n) % MOD) % MOD + MOD) % MOD);
}
