#include <algorithm>
#include <cstdio>

#define int long long

const int N = 2e5 + 10;

int a[N];
int dp[N][2], sum[N][2];

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int n;
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%lld", &a[i]);
    int flag = 0, maxn = a[1];
    if (a[1] < 0)
      flag = -1;
    else
      flag = 1;
    int ans = 0, pre = flag;
    for (int i = 2; i <= n; ++i) {
      int typ = a[i] > 0 ? 1 : -1;
      if (typ == pre)
        maxn = std::max(maxn, a[i]);
      else
        ans += maxn, maxn = a[i], pre = typ;
    }
    printf("%lld\n", ans + maxn);
  }
  return 0;
}
