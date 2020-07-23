#include <cstdio>

#define int long long

const int N = 1e5 + 10;

int n, m;
int s1[N], s2[N];
struct FenwickTree {
  int t[N];

#define lowbit(x) (x & -x)

  void Add(int p, int v) {
    for (; p <= n; p += lowbit(p))
      t[p] += v;
  }

  int Ask(int p) {
    int res = 0;
    for (; p >= 1; p -= lowbit(p))
      res += t[p];
    return res;
  }
} ft;

int a[N];

int Query(int l, int r) {
  return s2[r] - s2[l - 1] - (l - 1) * (s1[r] - s1[l - 1]);
}

signed main() {
  scanf("%lld%lld", &n, &m);
  for (int i = 1; i <= n; ++i)
    s1[i] = s1[i - 1] + i, s2[i] = s2[i - 1] + i * i;
  // while (true) {
  //   int x, y;
  //   scanf("%lld%lld", &x, &y);
  //   printf("%lld\n", Query(x, y));
  // }
  while (m--) {
    int opt, x;
    scanf("%lld%lld", &opt, &x);
    if (opt == 1) {
      if (a[x])
        continue;
      a[x] = 1;
      ft.Add(x, 1);
    } else if (opt == 2) {
      if (!a[x])
        continue;
      a[x] = 0;
      ft.Add(x, -1);
    } else {
      if (a[x]) {
        printf("0\n");
        continue;
      }
      int l = 0, r = x, ql = 0, qr = n, p = ft.Ask(x);
      while (l <= r) {
        int mid = (l + r) >> 1;
        if (ft.Ask(mid) < p)
          l = mid + 1;
        else
          r = mid - 1, ql = mid;
      }
      l = x, r = n, ++ql;
      while (l <= r) {
        int mid = (l + r) >> 1;
        // printf("l: %lld %lld %lld %lld\n", l, r, ft.Ask(mid), p);
        if (ft.Ask(mid) > p)
          r = mid - 1;
        else
          l = mid + 1, qr = mid;
      }
      // printf("> %lld %lld\n", ql, qr);
      printf("%lld\n", Query(ql, qr));
    }
  }
  return 0;
}
