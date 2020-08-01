#include <cstdio>

#define int long long

const int N = 1e5 + 10;

int a[N];

struct SegmentTree {
  int sum[N << 2], tag[N << 2];

#define lc (rt << 1)
#define rc (rt << 1 | 1)
#define ls lc, l, mid
#define rs rc, mid + 1, r

  void PushUp(int rt) { sum[rt] = sum[lc] + sum[rc]; }

  void PushDown(int rt, int l, int r) {
    if (tag[rt]) {
      int mid = (l + r) >> 1;
      sum[lc] += (mid - l + 1) * tag[rt], sum[rc] += (r - mid) * tag[rt];
      tag[lc] += tag[rt], tag[rc] += tag[rt];
      tag[rt] = 0;
    }
  }

  void Build(int rt, int l, int r) {
    if (l == r)
      return sum[rt] = a[l], void();
    int mid = (l + r) >> 1;
    Build(ls), Build(rs);
    PushUp(rt);
  }

  void Update(int rt, int l, int r, int ql, int qr, int k) {
    if (ql <= l && r <= qr)
      return sum[rt] += (r - l + 1) * k, tag[rt] += k, void();
    int mid = (l + r) >> 1;
    PushDown(rt, l, r);
    if (ql <= mid)
      Update(ls, ql, qr, k);
    if (qr > mid)
      Update(rs, ql, qr, k);
    PushUp(rt);
  }

  int Query(int rt, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
      return sum[rt];
    int mid = (l + r) >> 1, res = 0;
    PushDown(rt, l, r);
    if (ql <= mid)
      res += Query(ls, ql, qr);
    if (qr > mid)
      res += Query(rs, ql, qr);
    return res;
  }
} st;

signed main() {
  int n, m;
  scanf("%lld%lld", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]);
  st.Build(1, 1, n);
  while (m--) {
    int opt, l, r, k;
    scanf("%lld%lld%lld", &opt, &l, &r);
    if (opt == 1) {
      scanf("%lld", &k);
      st.Update(1, 1, n, l, r, k);
    } else {
      printf("%lld\n", st.Query(1, 1, n, l, r));
    }
  }
  return 0;
}
