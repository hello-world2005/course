// from dead_X

#include <cstdio>
#include <cstdlib>

#define int long long

const int MOD = 1e9 + 7;

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % MOD)
    if (b & 1)
      res = 1ll * res * a % MOD;
  return res;
}

long long miu[5000003],prime[5000003],cnt;
bool v[5000003];

long long inv4 = FastPow(4, MOD - 2);
void init(int n) {
  v[1] = miu[1] = 1;
  int cnt = 0;
  for (int i = 2; i <= n; ++i) {
    if (!v[i])
      prime[++cnt] = i, miu[i] = -1;
    for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
      v[i * prime[j]] = 1;
      if (i % prime[j])
        miu[i * prime[j]] = -miu[i];
      else {
        miu[i * prime[j]] = 0;
        break;
      }
    }
  }
}
long long f(int k) {
  return k * k % MOD * (k + 1) % MOD * (k + 1) % MOD * inv4 % MOD;
}
signed main() {
  int n, m;
  scanf("%lld%lld", &n, &m);
  int k = n / m, ans = 0;
  init(k);
  if (n < m)
    puts("0"), exit(0);
  if (n == m)
    printf("%lld\n", n * n % MOD), exit(0);
  for (int i = 1; i <= k; i++)
    ans += miu[i] * f(k / i) * i % MOD * i % MOD, ans %= MOD;
  ++ans += MOD, ans %= MOD;
  printf("%lld\n", ans * m % MOD * m % MOD * FastPow(2, MOD - 2) % MOD);
  return 0;
}