#include <algorithm>
#include <cstdio>

#define int long long

const int N = 2e5 + 10;

int n;
int a[N], b[N];

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
      b[i] = 0;
    for (int i = 1; i <= n; ++i)
      scanf("%lld", &a[i]), ++b[a[i]];
    int t = 0, ans = 0;
    for (int i = 1; i <= n; ++i) {
      ans += (t + b[i]) / i;
      t = (t + b[i]) % i;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
