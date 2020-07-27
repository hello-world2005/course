#include <cstdio>
#include <cstring>

typedef long long ll;

const int N = 5e6 + 10;

ll f[N];
int vis[N];

int main() {
  ll x, a, c, d, ans = 0;
  scanf("%lld%lld%lld%lld", &x, &a, &c, &d);
  memset(vis, -1, sizeof(vis));
  for (ll m = 1; m <= d; ++m) {
    f[0] = x % m;
    ll qwq = 1;
    vis[f[0]] = 0;
    ll ed = 0;
    for (ll i = 0;; ++i) {
      f[i + 1] = (a * f[i] + c) % m;
      if (~vis[f[i + 1]]) {
        qwq = i + 1 - vis[f[i + 1]];
        ed = i + 1;
        break;
      }
      vis[f[i + 1]] = i + 1;
    }
    for (ll i = 0; i <= ed; ++i)
      vis[f[i]] = -1;
    ans += qwq;
  }
  printf("%lld\n", ans);
  return 0;
}
