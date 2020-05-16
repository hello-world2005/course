#include <cstdio>

#define int long long

const int MOD = 998244353;
const int N = 2e5 + 10;

int FastPow(int a, int b) {
  a %= MOD;
  int res = 1;
  while (b) {
    if (b & 1)
      res = res * a % MOD;
    a = a * a % MOD;
    b >>= 1;
  }
  return res;
}

int n, m, a;
int b[N];

signed main() {
  scanf("%lld%lld%lld", &n, &m, &a);
  for (int i = 1; i <= m; ++i)
    scanf("%lld", &b[i]);
  int ans = FastPow(a, n - b[m] * 2);
  for (int i = 1; i <= m; ++i)
    ans = ans * FastPow(a, b[i] - b[i - 1]) % MOD *
          (FastPow(a, b[i] - b[i - 1]) + 1 + MOD) % MOD * 499122177 % MOD;
  printf("%lld", ans);
  return 0;
}
