#include <algorithm>
#include <cstdio>

#define int long long

const int N = 2e5 + 10;

int a[N], b[N];
struct Node {
  int v, pos;

  Node() : v(0), pos(0) {}

  bool operator<(const Node& rhs) const { return v < rhs.v; }
  bool operator<(const int& rhs) const { return v < rhs; }
} c[N];
int lnk[N];

struct SegmentTree {
  int t[N << 2];

#define lc (rt << 1)
#define rc (rt << 1 | 1)
#define ls lc, l, mid
#define rs rc, mid + 1, r

  void PushUp(int rt) { t[rt] = std::max(t[lc], t[rc]); }

  void Build(int rt, int l, int r) {
    if (l == r)
      return t[rt] = a[l], void();
    int mid = (l + r) >> 1;
    Build(ls), Build(rs), PushUp(rt);
  }

  int Query(int rt, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
      return t[rt];
    int mid = (l + r) >> 1, res = 0;
    if (ql <= mid)
      res = std::max(res, Query(ls, ql, qr));
    if (qr > mid)
      res = std::max(res, Query(rs, ql, qr));
    return res;
  }
} st;

signed main() {
  int n, m, x, y, k;
  scanf("%lld%lld%lld%lld%lld", &n, &m, &x, &k, &y);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]), c[i].v = a[i], c[i].pos = i;
  for (int i = 1; i <= m; ++i)
    scanf("%lld", &b[i]);
  st.Build(1, 1, n);
  // std::sort(c + 1, c + n + 1);
  int maxn = 0;
  for (int i = 1, pos = 1; i <= m; ++i) {
    // int pos = std::lower_bound(c + 1, c + n + 1, b[i]) - c;
    for (; pos <= n; ++pos)
      if (b[i] == a[pos])
        break;
    // if (pos < maxn)
    //   return printf("-1\n"), 0;
    maxn = std::max(maxn, pos);
    lnk[i] = pos;
  }
  // for (int i = 1; i <= m; ++i)
  //   printf("%lld ", lnk[i]);
  // printf("\n");
  for (int i = 1; i <= m; ++i)
    if (lnk[i] == 0 || lnk[i] > n)
      return printf("-1\n"), 0;
  int ans = 0;
  lnk[0] = 0, lnk[m + 1] = n + 1;
  for (int i = 1; i <= m + 1; ++i) {
    int l = lnk[i - 1] + 1, r = lnk[i] - 1;
    // printf("%lld %lld\n", l, r);
    if (l > r)
      continue;
    int maxn = st.Query(1, 1, n, l, r);
    if (maxn > a[l - 1] && maxn > a[r + 1] && r - l + 1 < k)
      return printf("-1\n"), 0;
    if (maxn > a[l - 1] && maxn > a[r + 1]) {
      int len = r - l + 1;
      int k1 = len / k, k2 = len % k;
      ans += std::min(k1 * x + k2 * y, (len - k) * y + x);
    } else {
      int len = r - l + 1;
      int k1 = len / k, k2 = len % k;
      ans += std::min(k1 * x + k2 * y, len * y);
    }
  }
  printf("%lld\n", ans);
  return 0;
}
