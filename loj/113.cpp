#include <cstdio>

#define int long long

const int N = 60;

int n;
int a[N];
int d[N];

signed main() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]);
  for (int i = 1; i <= n; ++i) {
    int x = a[i];
    for (int j = 52; j >= 0; --j)
      if (x >> j & 1ll) {
        if (d[j]) {
          x ^= d[j];
        } else {
          d[j] = x;
          break;
        }
      }
  }
  int ans = 0;
  for (int i = 52; i >= 0; --i)
    if ((ans ^ d[i]) > ans)
      ans ^= d[i];
  printf("%lld\n", ans);
  return 0;
}
