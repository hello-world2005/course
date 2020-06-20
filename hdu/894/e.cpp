#include <cstdio>
#include <cstring>

#define int long long

const int N = 1e5 + 10;

int f[N], s[N], d[N];

int Find(int u) {
  return u == f[u] ? u : Find(f[u]);
}

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int n, m;
    scanf("%lld%lld", &n, &m);
    int now = n * (n - 1) / 2;
    f[1] = 1;
    s[1] = n;
    for (int i = 2; i <= n; ++i)
      f[i] = i / 2;
    // printf("%d\n", s[6]);
    s[2] = 5, s[3] = s[4] = 3, s[5] = s[6] = s[7] = s[8] = s[9] = 1;
    while (m--) {
      int q;
      scanf("%lld", &q);
      int u = q, v = q / 2;
      if (f[u] == v) {
        v = Find(v);
        f[u] = u;
        s[v] -= (s[u] - d[u]);
        d[v] += (s[u] - d[u]);
        now -= (s[u] - d[u]) * s[v];
        printf("%lld %lld %lld %lld\n", s[u], d[u], s[v], d[v]);
      }
      // else {
      //   f[u] = v;
      //   s[v] += (s[u] - d[u]);
      //   d[v] -= (s[u] - d[u]);
      //   now += (s[u] - d[u]) * (s[v] - d[v]);
      // }
      printf("%lld\n", now);
    }
  }
  return 0;
}
