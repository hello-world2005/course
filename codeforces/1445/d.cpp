#include <algorithm>
#include <cstdio>

#define int long long

const int N = 3e5 + 10;
const int MOD = 998244353;

int a[N];
int sum[2];

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = a * a % MOD)
    if (b & 1)
      res = res * a % MOD;
  return res;
}

int fac[N], inv[N];

void Init(const int& n) {
  fac[0] = 1;
  for (int i = 1; i <= n; ++i)
    fac[i] = fac[i - 1] * i % MOD, inv[i] = FastPow(fac[i], MOD - 2);
}

int C(int n, int m) {
  return fac[n] * inv[n - m] % MOD * inv[m] % MOD;
}

signed main() {
  int n;
  scanf("%lld", &n);
  Init(n << 1);
  for (int i = 1; i <= 2 * n; ++i)
    scanf("%lld", &a[i]);
  std::sort(a + 1, a + 2 * n + 1);
  for (int i = 1; i <= 2 * n; ++i)
    (sum[i > n] += a[i]) %= MOD;
  printf("%lld\n", (sum[1] - sum[0] + MOD) % MOD * C(2 * n, n) % MOD);
}
