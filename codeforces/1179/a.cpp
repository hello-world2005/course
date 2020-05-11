#include <algorithm>
#include <cstdio>

#define int long long

typedef long long ll;

const int N = 4e5 + 10;

int a[N];
int ans[N << 1][2];

signed main() {
  int n, q;
  scanf("%lld%lld", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]);
  for (int i = 1, j = 1; i <= (2 * n); ++i, ++j) {
    ans[i][0] = a[j];
    ans[i][1] = a[j + 1];
    a[j + n] = std::min(a[j], a[j + 1]);
    a[j + 1] = std::max(a[j], a[j + 1]);
  }
  while (q--) {
    ll k;
    scanf("%lld", &k);
    if (k <= (2 * n))
      printf("%lld %lld\n", ans[k][0], ans[k][1]);
    else
      printf("%lld %lld\n", ans[(k - n) % (n - 1) + n][0],
             ans[(k - n) % (n - 1) + n][1]);
  }
  return 0;
}
