#include <cstdio>
#include <cstring>

typedef long long ll;

const int N = 20;
const int M = 2530;
const int MOD = 2520;

ll dp[N][M][50];
int n[N], len;
int qwq[MOD];

ll cnt;

ll Gcd(int a, int b) {
  if (b == 0)
    return a;
  return Gcd(b, a % b);
}

ll Lcm(int a, int b) {
  return a * b / Gcd(a, b);
}

ll Dfs(int pos, int mod, int mask, bool ismax) {
  // printf("%d\n", mask);
  ++cnt;
  if (pos < 1)
    return mod % mask == 0;
  if (!ismax && ~dp[pos][mod][qwq[mask]])
    return dp[pos][mod][qwq[mask]];
  int lim = ismax ? n[pos] : 9;
  ll res = 0;
  for (int i = 0; i <= lim; ++i)
    res += Dfs(pos - 1, (mod * 10 + i) % MOD, i >= 1 ? Lcm(mask, i) : mask,
               ismax && (i == lim));
  if (!ismax)
    dp[pos][mod][qwq[mask]] = res;
  return res;
}

ll Solve(ll x) {
  len = 0;
  while (x) {
    n[++len] = x % 10;
    x /= 10;
  }
  return Dfs(len, 0, 1, true);
}

int main() {
  int T;
  scanf("%d", &T);
  int qaq = 0;
  memset(dp, -1, sizeof(dp));
  for (int i = 1; i <= MOD; ++i)
    if (MOD % i == 0)
      qwq[i] = ++qaq;
  while (T--) {
    ll a, b;
    scanf("%lld%lld", &a, &b);
    printf("%lld\n", Solve(b) - Solve(a - 1));
    // printf("%lld %lld\n", Solve(a - 1), Solve(b));
    // printf("%lld\n", cnt);
  }
  return 0;
}
