#include <algorithm>
#include <cstdio>

const int N = 5e6 + 10;
const int MOD = 1e9 + 7;

int n, m, k, ans;

bool vis[N];
int pri[N], cnt;
int f[N];

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % MOD)
    if (b & 1)
      res = 1ll * res * a % MOD;
  return res;
}

void Sieve() {
  f[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!vis[i])
      pri[++cnt] = i, f[i] = 1ll * (FastPow(i, k) - 1) % MOD;
    for (int j = 1; j <= cnt && i * pri[j] < N; ++j) {
      vis[i * pri[j]] = true;
      if (i % pri[j] == 0) {
        f[i * pri[j]] = 1ll * f[i] * FastPow(pri[j], k) % MOD;
        break;
      }
      f[i * pri[j]] = 1ll * f[i] * f[pri[j]] % MOD;
    }
  }
  for (int i = 2; i < N; ++i)
    f[i] = (f[i] + f[i - 1]) % MOD;
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  Sieve();
  if (n > m)
    std::swap(n, m);
  for (int l = 1, r; l <= n; l = r + 1) {
    r = std::min(n / (n / l), m / (m / l));
    ans = (ans + 1ll * (n / l) * (m / l) % MOD * (f[r] - f[l - 1]) % MOD) % MOD;
  }
  printf("%d\n", (ans + MOD) % MOD);
  return 0;
}
