#include <cstdio>

#define int long long

const int MOD = 998244353;
const int N = 5e5 + 10;

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % MOD)
    if (b & 1)
      res = 1ll * res * a % MOD;
  return res;
}

int fac[N], inv[N];

void Init() {
  fac[0] = inv[0] = 1;
  for (int i = 1; i < N; ++i) {
    fac[i] = 1ll * fac[i - 1] * i % MOD;
    inv[i] = FastPow(fac[i], MOD - 2);
  }
}

int C(int a, int b) {
  if (a > b)
    return 0;
  return 1ll * fac[b] * inv[b - a] % MOD * inv[a] % MOD;
}

signed main() {
  Init();
  int n, k, ans = 0;
  scanf("%lld%lld", &n, &k);
  for (int i = 1; i <= n; ++i) {
    int div = n / i;
    // printf("%lld\n", div);
    ans = (ans + C(k - 1, div - 1)) % MOD;
  }
  printf("%lld\n", ans);
  return 0;
}
