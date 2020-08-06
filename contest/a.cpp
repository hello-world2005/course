#include <algorithm>
#include <cstdio>

typedef long long ll;

const int MOD = 1e9 + 7;

ll Phi(ll n) {
  ll res = 1;
  for (ll i = 2; i * i <= n; i++)
    if (n % i == 0) {
      n /= i, res *= i - 1;
      while (n % i == 0)
        n /= i, res *= i;
    }
  if (n > 1)
    res *= n - 1;
  return res;
}

int main() {
  ll n, m;
  scanf("%lld", &n);
  m = Phi(n);
  ll ans1 = 0, ans2 = 0;
  for (ll l = 1, r = 0; l <= n; l = r + 1) {
    r = n / (n / l);
    (ans1 += n / l * (std::min(r, n) - l + 1)) %= MOD;
  }
  for (ll l = 1, r = 0; l <= m; l = r + 1) {
    r = n / (n / l);
    (ans2 += n / l * (std::min(r, m) - l + 1)) %= MOD;
  }
  printf("%lld\n", ans1 * ans2 % MOD);
  return 0;
}
