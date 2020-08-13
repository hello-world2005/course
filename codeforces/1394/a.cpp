#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>
typedef long long ll;

#define int long long
const int N = 1e5 + 10;
ll s[N];

int a[N];

int x[N], y[N];

signed main() {
  int n, d, m;
  scanf("%lld%lld%lld", &n, &d, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]);
  int cnt1 = 0, cnt2 = 0;
  for (int i = 1; i <= n; ++i)
    if (a[i] <= m)
      x[++cnt1] = a[i];
    else
      y[++cnt2] = a[i];
  std::sort(x + 1, x + cnt1 + 1, std::greater<int>());
  std::sort(y + 1, y + cnt2 + 1, std::greater<int>());

  ll ans = 0;
  ++d;

  for (int i = 1; i <= n; ++i)
    y[i] += y[i - 1];
  for (int i = 1; i <= n; ++i)
    x[i] += x[i - 1];

  for (int i = 0; i <= cnt1; ++i) {
    int qwq;
    if ((n - i) % d)
      qwq = (n - i) / d + 1;
    else
      qwq = (n - i) / d;
    ans = std::max(ans, x[i] + y[qwq]);
  }
  printf("%lld\n", ans);
  return 0;
}
