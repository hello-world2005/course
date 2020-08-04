#include <cstdio>

const int N = 510;
const int MOD = 998244353;

int n, m;
int a[N];

int f[N], g[N], deg;

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % MOD)
    if (b & 1)
      res = 1ll * res * a % MOD;
  return res;
}

int F(int x) {
  int res = 0;
  for (int i = deg - 1; i >= 0; --i)
    res = 1ll * res * x % MOD, res = (res + f[i]) % MOD;
  return res;
}

int G(int x) {
  int res = 0;
  for (int i = deg - 1; i >= 0; --i)
    res = 1ll * res * x % MOD, res = (res + g[i]) % MOD;
  return res;
}

int QwQ(int x) {
  int res = 0;
  for (int i = 1; i <= n; ++i)
    res = (res + 1ll * a[i] * FastPow(x, a[i]) % MOD) % MOD;
  return res;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  g[0] = 1;
  for (int i = 1; i <= n + 2; ++i) {
    int x = i, y = QwQ(i);
    ++deg;
    y -= F(x);
    y = (y + MOD) % MOD;
    // printf("> %d\n", y);
    y = 1ll * y * FastPow(G(x), MOD - 2) % MOD;
    for (int i = 0; i < deg; ++i)
      f[i] = (f[i] + 1ll * y * g[i] % MOD) % MOD;
    for (int i = deg - 1; i >= 0; --i)
      g[i + 1] = (g[i + 1] + g[i]) % MOD, g[i] = 1ll * g[i] * (MOD - x) % MOD;
  }
  printf("%d\n", F(m));
  return 0;
}
