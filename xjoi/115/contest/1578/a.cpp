#include <algorithm>
#include <cstdio>

#define int long long

const int N = 1e5 + 10;

int fa[N];

int FindFa(int u) {
  if (u == fa[u])
    return u;
  return fa[u] = FindFa(fa[u]);
}

int a[N], b[N];

signed main() {
  int n;
  scanf("%lld", &n);
  int maxn = 0, ans = 0;
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]), b[a[i]] ? ans += a[i] : b[a[i]] = fa[i] = i, maxn = std::max(maxn, a[i]);
  for (int i = maxn; i >= 1; --i) {
    int res = 0;
    for (int j = 1; i * j <= maxn; ++j)
      if (b[i * j]) {
        if (!res) {
          res = b[i * j];
        } else {
          int fu = FindFa(res), fv = FindFa(b[i * j]);
          if (fu != fv)
            fa[fu] = fv, ans += i;
        }
      }
  }
  printf("%lld\n", ans);
  return 0;
}
