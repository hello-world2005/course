#include <algorithm>
#include <cstdio>

#define int long long

const int N = 70000;
const int MOD = 998244353;
const int G = 3;
const int GI = 332748118;

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = a * a % MOD)
    if (b & 1)
      res = res * a % MOD;
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
      for (int k = 0; k < i; ++k, w = w * wn % MOD) {
        int x = a[j + k], y = w * a[i + j + k] % MOD;
        a[j + k] = (x + y) % MOD;
        a[i + j + k] = (x - y + MOD) % MOD;
      }
    }
  }
  if (opt == -1) {
    int inv = FastPow(n, MOD - 2);
    for (int i = 0; i < n; ++i)
      a[i] = a[i] * inv % MOD;
  }
}

typedef std::pair<int, int> pii;

pii a[N];
int f[N], ans[N];

signed main() {
  int n, l, m, k;
  scanf("%lld%lld%lld", &n, &l, &m);
  int lim = 1, cnt = 0;
  while (lim < n)
    lim <<= 1, ++cnt;
  for (int i = 0; i < lim; ++i)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (cnt - 1));
  for (int i = 1; i <= m; ++i)
    scanf("%lld%lld", &a[i].first, &a[i].second);
  std::sort(a + 1, a + m + 1);
  scanf("%lld", &k);
  for (int i = 1, x; i <= k; ++i)
    scanf("%lld", &x), x %= n, ++f[x];
  Ntt(f, lim, 1);
  ans[0] = 1;
  for (int i = 1; i <= m; ++i) {
    Ntt(ans, lim, 1);
    for (int j = 0; j < n; ++j)
      ans[j] = ans[j] * FastPow(f[j], a[i].first - a[i - 1].first) % MOD;
    Ntt(ans, lim, -1);
    ans[a[i].second] = 0;
  }
  Ntt(ans, lim, 1);
  for (int i = 0; i < n; ++i)
    ans[i] = ans[i] * FastPow(f[i], l - a[m].first) % MOD;
  Ntt(ans, lim, -1);
  printf("%lld\n", ans[0]);
  return 0;
}
