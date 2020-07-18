#include <algorithm>
#include <cstdio>

#define int long long

const int N = 4e5 + 10;
const int MOD = 998244353;

int rev[N];

int FastPow(int a, int b, int MOD) {
  int res = 1;
  b = (b + MOD - 1) % (MOD - 1);
  for (; b; b >>= 1, a = 1ll * a * a % MOD)
    if (b & 1)
      res = 1ll * res * a % MOD;
  return res;
}

void Ntt(int* a, int n, int MOD, int G) {
  for (int i = 0; i < n; ++i)
    if (i < rev[i])
      std::swap(a[i], a[rev[i]]);
  for (int i = 1; i < n; i <<= 1) {
    int wn = FastPow(G, (MOD - 1) / (i << 1), MOD);
    for (int j = 0; j < n; j += (i << 1)) {
      int w = 1;
      for (int k = 0; k < i; ++k, w = 1ll * w * wn % MOD) {
        int x = a[j + k], y = 1ll * w * a[i + j + k] % MOD;
        a[j + k] = (x + y) % MOD;
        a[i + j + k] = (x - y + MOD) % MOD;
      }
    }
  }
}

int fac[N], inv[N];

void Init() {
  fac[0] = inv[0] = 1;
  for (int i = 1; i < N; ++i) {
    fac[i] = 1ll * fac[i - 1] * i % MOD;
    inv[i] = FastPow(fac[i], MOD - 2, MOD);
  }
}

int A[N], B[N];

int Inv(int x) {
  if (x < 0)
    x += MOD;
  return FastPow(x, MOD - 2, MOD);
}

int F(int a, int b, int c) {
  if (c == 0)
    return 1;
  if (c == 1)
    return b;
  return (1ll * ((a - 1ll * a * FastPow(c, b, MOD) % MOD + MOD) % MOD) * Inv(1 - c)) % MOD;
}

signed main() {
  int n, l, c;
  Init();
  scanf("%lld%lld%lld", &n, &l, &c);
  int lim = 1, cnt = 0;
  while (lim <= (2 * n))
    lim <<= 1, ++cnt;
  for (int i = 0; i < lim; ++i)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (cnt - 1));
  for (int i = 0, j = 1; i <= n; ++i, j *= -1)
    A[i] = (1ll * j * F(FastPow(c, 1 - i, MOD), l, FastPow(c, 1 - i, MOD)) %
                MOD * inv[i] % MOD +
            MOD) %
           MOD;
  for (int i = 0; i <= n; ++i)
    B[i] = inv[i];
  Ntt(A, lim, MOD, 3), Ntt(B, lim, MOD, 3);
  for (int i = 0; i < lim; ++i)
    A[i] = 1ll * A[i] * B[i] % MOD;
  Ntt(A, lim, MOD, Inv(3));
  for (int i = 0, inv = Inv(lim); i < lim; ++i)
    A[i] = 1ll * A[i] * inv % MOD;
  int t = F(c % MOD, l, c % MOD);
  for (int i = 1; i <= n; ++i)
    A[i] = (t - 1ll * A[i] * fac[i] % MOD + MOD) % MOD;
  for (int i = 1; i <= n; ++i)
    printf("%lld\n", A[i]);
  return 0;
}
