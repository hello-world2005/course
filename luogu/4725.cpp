#include <algorithm>
#include <cstdio>

const int N = 2e5 + 10;
const int MOD = 998244353;
const int G = 3, GI = 332748118;

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % MOD)
    if (b & 1)
      res = 1ll * res * a % MOD;
  return res;
}

int rev[N];

void Ntt(int* a, int n, int opt) {
  for (int i = 0; i < n; ++i)
    if (i < rev[i])
      std::swap(a[i], a[rev[i]]);
  for (int i = 1; i < n; i <<= 1) {
    int wn = FastPow(opt == 1 ? G : GI, (MOD - 1) / (i << 1));
    for (int j = 0; j < n; j += (i << 1)) {
      int w = 1;
      for (int k = 0; k < i; ++k, w = 1ll * w * wn % MOD) {
        int x = a[j + k], y = 1ll * w * a[i + j + k] % MOD;
        a[j + k] = (x + y) % MOD;
        a[i + j + k] = (x - y + MOD) % MOD;
      }
    }
  }
  if (opt == -1) {
    int inv = FastPow(n, MOD - 2);
    for (int i = 0; i < n; ++i)
      a[i] = 1ll * a[i] * inv % MOD;
  }
}

int f[N], g[N];
int c[N], d[N];

void Inv(int* a, int* b, int n) {
  if (n == 1)
    return g[0] = FastPow(f[0], MOD - 2), void();
  Inv(f, g, n >> 1);
  int lim = 1, cnt = 0;
  while (lim <= n)
    lim <<= 1, ++cnt;
  for (int i = 0; i < lim; ++i)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (cnt - 1));
  for (int i = 0; i < n; ++i)
    c[i] = f[i], d[i] = g[i];
  for (int i = n; i < lim; ++i)
    c[i] = d[i] = 0;
  Ntt(c, n, 1), Ntt(d, n, 1);
  for (int i = 0; i < lim; ++i)
    c[i] = 1ll * c[i] * d[i] % MOD * d[i] % MOD;
  Ntt(c, n, -1);
  for (int i = 0; i < n; ++i)
    g[i] = ((2ll * g[i] % MOD - c[i]) % MOD + MOD) % MOD;
}

void Ln(int* a, int* b, int n) {
  static int f[N], g[N];
  for (int i = 1; i < n; ++i)
    f[i - 1] = 1ll * a[i] * i % MOD;
  Inv(b, g, n);
  Ntt(f, n, 1), Ntt(g, n, 1);
  for (int i = 0; i < n; ++i)
    f[i] = 1ll * f[i] * g[i] % MOD;
  Ntt(f, n, -1);
  for (int i = 1; i < n; ++i)
    b[i] = 1ll * a[i - 1] * FastPow(i, MOD - 2) % MOD;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &f[i]);
  int lim = 1;
  while (lim <= n)
    Ln(f, g, (lim <<= 1));
  for (int i = 0; i < n; ++i)
    printf("%d ", g[i]);
  printf("\n");
  return 0;
}
