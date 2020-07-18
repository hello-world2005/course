#include <algorithm>
#include <cstdio>
#include <unordered_map>

#define int long long

const int N = 1e6 + 10;
const int MOD = 998244353;

int prime[N], cnt;
bool vis[N];
int mu[N];
int mui[N], muii[N];

void Init() {
  mu[1] = mui[1] = muii[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!vis[i])
      prime[++cnt] = i, mu[i] = -1;
    mui[i] = (mu[i] * i + MOD) % MOD, muii[i] = (mu[i] * i * i + MOD) % MOD;
    for (int j = 1; j <= cnt && i * prime[j] < N; ++j) {
      vis[i * prime[j]] = true;
      if (i % prime[j] == 0) {
        mu[i * prime[j]] = 0;
        break;
      }
      mu[i * prime[j]] = -mu[i];
    }
  }
  for (int i = 2; i < N; ++i)
    (mu[i] += mu[i - 1] + MOD) %= MOD, (mui[i] += mui[i - 1]) %= MOD,
        (muii[i] += muii[i - 1]) %= MOD;
}

int GetSum(int x) { return x * (x + 1) / 2 % MOD; }

signed main() {
  Init();
  int T;
  scanf("%lld", &T);
  // for (int i = 1; i <= 10; ++i)
  //   printf("%lld %lld %lld\n", mu[i], mui[i], muii[i]);
  while (T--) {
    int n, m;
    scanf("%lld%lld", &n, &m);
    --n, --m;
    if (n > m)
      std::swap(n, m);
    if (n == 0) {
      printf("%d\n", m != 0);
      continue;
    }
    int ans = 0;
    // printf("%lld %lld %lld\n", mu[8627], mui[8267], muii[8267]);
    for (int l = 1, r = 0; l <= n; l = r + 1) {
      r = std::min(n / (n / l), m / (m / l));
      // printf("%lld %lld\n", l, r);
      int x = n / l, y = m / l;
      ans = ((ans +
              (x * y % MOD * (n + 1) % MOD * (m + 1) % MOD *
               (mu[r] - mu[l - 1] + MOD) % MOD) -
              ((mui[r] - mui[l - 1] + MOD) % MOD *
               (x * GetSum(y) % MOD * (n + 1) % MOD +
                GetSum(x) * y % MOD * (m + 1) % MOD)) +
              (GetSum(x) * GetSum(y) % MOD * (muii[r] - muii[l - 1] + MOD) %
               MOD) -
              ((x / 2) * (y / 2) % MOD * (n + 1) % MOD * (m + 1) % MOD *
               (mu[r] - mu[l - 1] + MOD) % MOD) +
              (2 * (mui[r] - mui[l - 1] + MOD) % MOD *
               ((x / 2) * GetSum(y / 2) % MOD * (n + 1) % MOD +
                (y / 2) * GetSum(x / 2) % MOD * (m + 1) % MOD)) -
              4 * (GetSum(x / 2) * GetSum(y / 2) % MOD *
                   (muii[r] - muii[l - 1] + MOD) % MOD)) %
                 MOD +
             MOD) %
            MOD;
    }
    printf("%lld\n", ((ans + MOD) % MOD * 2 % MOD + n + m + 2) % MOD);
  }
  return 0;
}
