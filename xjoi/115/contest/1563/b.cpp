#include <algorithm>
#include <cstdio>

const int MOD = 323232323;

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % MOD)
    if (b & 1)
      res = 1ll * res * a % MOD;
  return res;
}

int Inv(int a) {
  return FastPow(a, MOD - 2);
}

const int N = 2e5 + 10;

int a[N];

int fac[N], inv[N];

void Init() {
  fac[0] = inv[0] = 1;
  for (int i = 1; i < N; ++i)
    fac[i] = 1ll * fac[i - 1] * i % MOD,
    inv[i] = Inv(fac[i]);
}

int C(int n, int m) {
  return 1ll * fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int dp[N][2];

int main() {
  int n, maxn = 0;
  scanf("%d", &n);
  Init();
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), maxn = std::max(maxn, a[i]);
  dp[1][0] = FastPow(Inv(2), a[1]) - 1;
  for (int i = 2; i <= maxn; ++i) {
    int now = 1ll * C(a[1] + i - 2, i - 1) * FastPow(Inv(2), a[1] + i - 1) % MOD;
    dp[i][0] = 1ll * i * (1ll * dp[i - 1][0] * Inv(i - 1) % MOD + now) % MOD;
    dp[i][1] = (dp[i - 1][1] + 1ll * (i - 1) * now % MOD) % MOD;
  }
  int ans = 0;
  for (int i = 2; i <= n; ++i)
    ans = (ans + dp[a[i]][1] - dp[a[i]][0]) % MOD;
  printf("%d\n", ((ans + a[1]) % MOD + MOD) % MOD);
  return 0;
}
