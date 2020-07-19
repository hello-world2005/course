#include <algorithm>
#include <cstdio>

#define int long long

const int N = 1e5 + 10;

struct Node {
  int a, b;

  bool operator<(const Node& rhs) const { return a > rhs.a; }
} a[N];
int v[N];
int sum[N];

int Bound(int k, int n) {
  int l = 1, r = n, res = 0;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (a[mid].a >= k)
      l = mid + 1, res = mid;
    else
      r = mid - 1;
  }
  return res;
}

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int n, m;
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= m; ++i)
      scanf("%lld%lld", &a[i].a, &a[i].b);
    std::sort(a + 1, a + m + 1);
    for (int i = 1; i <= m; ++i)
      sum[i] = sum[i - 1] + a[i].a;
    int ans = 0;
    for (int i = 1; i <= m; ++i) {
      int p = std::min(n, Bound(a[i].b, m));
      if (p < i)
        p = std::min(p, n - 1),
        ans = std::max(ans, (n - p - 1) * a[i].b + sum[p] + a[i].a);
      else
        ans = std::max(ans, (n - p) * a[i].b + sum[p]);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
