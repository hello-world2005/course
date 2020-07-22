#include <algorithm>
#include <cstdio>

const int N = 1e6 + 10;
const int MOD = 1e9 + 7;

bool vis[N];
int pri[N / 10], cnt;
int maxn;

void Sieve() {
  for (int i = 2; i < maxn; ++i) {
    if (!vis[i])
      pri[++cnt] = i;
    for (int j = 1; j <= cnt && i * pri[j] < N; ++j) {
      vis[i * pri[j]] = true;
      if (i % pri[j] == 0)
        break;
    }
  }
}

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % MOD)
    if (b & 1)
      res = 1ll * res * a % MOD;
  return res;
}

int f[N], g[N];
int mf[N], invf[N];  // pre-multiF invF

void Init() {
  int n = maxn;
  f[1] = mf[1] = invf[0] = invf[1] = 1;
  for (int i = 2; i <= n; ++i)
    f[i] = (f[i - 1] + f[i - 2]) % MOD, mf[i] = 1ll * mf[i - 1] * f[i] % MOD;
  int t = FastPow(mf[n], MOD - 2);
  for (int i = n; i >= 2; --i)
    invf[i] = 1ll * t * mf[i - 1] % MOD, t = 1ll * t * f[i] % MOD;
  for (int i = 1; i <= cnt; ++i)  // 只含有前 i 个质因子
    for (int j = n / pri[i]; j >= 1; --j) {
      int k = j * pri[i];
      f[k] = 1ll * f[k] * invf[j] % MOD;
      invf[k] = 1ll * invf[k] * f[j] % MOD;
    }
  for (int i = 2; i <= n; ++i)
    f[i] = 1ll * f[i] * f[i - 1] % MOD,
    invf[i] = 1ll * invf[i] * invf[i - 1] % MOD;
  // printf("%d %d\n", f[6], invf[6]);
}

int a[1010], b[1010];

int main() {
  int T;
  scanf("%d", &T);
  for (int i = 1; i <= T; ++i)
    scanf("%d%d", &a[i], &b[i]), maxn = std::max({maxn, a[i], b[i]});
  Sieve();
  Init();
  for (int i = 1; i <= T; ++i) {
    int n = a[i], m = b[i], res = 1;
    int minn = std::min(n, m);
    for (int l = 1, r = 0; l <= minn; l = r + 1) {
      r = std::min(n / (n / l), m / (m / l));
      // printf("%d %d\n", f[r], invf[l - 1]);
      res = (1ll * res *
             FastPow(1ll * f[r] * invf[l - 1] % MOD, 1ll * (n / l) * (m / l) % (MOD - 1))) %
            MOD;
    }
    printf("%d\n", res);
  }
  return 0;
}
