#include <algorithm>
#include <cstdio>
#include <unordered_map>

#define int long long

const int N = 8e6 + 10;
const int MOD = 1e9 + 7;

bool vis[N];
int prime[N], cnt;
int phi[N], sum_phi[N];

void Init() {
  phi[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!vis[i])
      prime[++cnt] = i, phi[i] = i - 1;
    for (int j = 1; j <= cnt && i * prime[j] < N; ++j) {
      vis[i * prime[j]] = true;
      if (i % prime[j] == 0) {
        phi[i * prime[j]] = phi[i] * prime[j];
        break;
      }
      phi[i * prime[j]] = phi[i] * phi[prime[j]];
    }
  }
  for (int i = 1; i < N; ++i)
    sum_phi[i] = (sum_phi[i - 1] + phi[i]) % MOD;
}

std::unordered_map<int, int> _phi;

int GetPhi(int x) {
  if (x < N)
    return phi[x];
  if (_phi.find(x) != _phi.end())
    return _phi[x];
  int res = x, _x = x;
  for (int i = 1; i <= cnt && prime[i] * prime[i] <= x; ++i) {
    if (x % prime[i] == 0) {
      res = res / prime[i] * (prime[i] - 1), x /= prime[i];
      while (x % prime[i] == 0)
        x /= prime[i];
    }
  }
  if (x > 1)
    res = res / x * (x - 1);
  res %= MOD;
  _phi.insert(std::make_pair(_x, res));
  return res;
}

const int INV2 = 5e8 + 4;

std::unordered_map<int, int> _sum_phi;

int SumPhi(int n) {
  if (n < N)
    return sum_phi[n];
  if (_sum_phi.find(n) != _sum_phi.end())
    return _sum_phi[n];
  int res = ((((n % MOD) * ((n + 1) % MOD)) % MOD) * INV2) % MOD;
  for (int l = 2, r; l <= n; l = r + 1) {
    r = n / (n / l);
    res = (res - (r - l + 1) % MOD * SumPhi(n / l) % MOD) % MOD;
  }
  return _sum_phi[n] = (res + MOD) % MOD;
}

signed main() {
  Init();
  int n, ans = 0;
  scanf("%lld", &n);
  for (int l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    ans = (ans + (2 * SumPhi(n / l) % MOD - 1 + MOD) % MOD *
                     (SumPhi(r) - SumPhi(l - 1) + MOD) % MOD) %
          MOD;
  }
  printf("%lld\n", ans);
  return 0;
}
