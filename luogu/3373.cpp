#include <cstdio>

#define int long long

const int N = 1e5 + 10;
int MOD;

int a[N];

struct SegmentTree {
  int sum[N << 2], tag1[N << 2], tag2[N << 2];

#define lc (rt << 1)
#define rc (rt << 1 | 1)
#define ls lc, l, mid
#define rs rc, mid + 1, r

  void PushUp(int rt) { sum[rt] = (sum[lc] + sum[rc]) % MOD; }

  void PushDown(int rt, int l, int r) {
    if (tag2[rt] != 1) {
      // int mid = (l + r) >> 1;
      (sum[lc] *= tag2[rt]) %= MOD, (sum[rc] *= tag2[rt]) %= MOD;
      (tag2[lc] *= tag2[rt]) %= MOD, (tag2[rc] *= tag2[rt]) %= MOD;
      (tag1[lc] *= tag2[rt]) %= MOD, (tag1[rc] *= tag2[rt]) %= MOD;
      tag2[rt] = 1;
    }
    if (tag1[rt]) {
      int mid = (l + r) >> 1;
      (sum[lc] += (mid - l + 1) * tag1[rt]) %= MOD,
          (sum[rc] += (r - mid) * tag1[rt]) %= MOD;
      (tag1[lc] += tag1[rt]) %= MOD, (tag1[rc] += tag1[rt]) %= MOD;
      tag1[rt] = 0;
    }
  }

  void Build(int rt, int l, int r) {
    tag2[rt] = 1;
    if (l == r)
      return sum[rt] = a[l] % MOD, void();
    int mid = (l + r) >> 1;
    Build(ls), Build(rs);
    PushUp(rt);
  }

  void Update1(int rt, int l, int r, int ql, int qr, int k) {
    if (ql <= l && r <= qr)
      return (sum[rt] += (r - l + 1) * k) %= MOD, (tag1[rt] += k) %= MOD,
             void();
    int mid = (l + r) >> 1;
    PushDown(rt, l, r);
    if (ql <= mid)
      Update1(ls, ql, qr, k);
    if (qr > mid)
      Update1(rs, ql, qr, k);
    PushUp(rt);
  }

  void Update2(int rt, int l, int r, int ql, int qr, int k) {
    if (ql <= l && r <= qr)
      return (sum[rt] *= k) %= MOD, (tag2[rt] *= k) %= MOD,
             (tag1[rt] *= k) %= MOD, void();
    int mid = (l + r) >> 1;
    PushDown(rt, l, r);
    if (ql <= mid)
      Update2(ls, ql, qr, k);
    if (qr > mid)
      Update2(rs, ql, qr, k);
    PushUp(rt);
  }

  int Query(int rt, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
      return sum[rt];
    int mid = (l + r) >> 1, res = 0;
    PushDown(rt, l, r);
    if (ql <= mid)
      (res += Query(ls, ql, qr)) %= MOD;
    if (qr > mid)
      (res += Query(rs, ql, qr)) %= MOD;
    return res;
  }
} st;

signed main() {
  int n, m, p;
  scanf("%lld%lld%lld", &n, &m, &p);
  MOD = p;
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]);
  st.Build(1, 1, n);
  while (m--) {
    int opt, l, r, k;
    scanf("%lld%lld%lld", &opt, &l, &r);
    if (opt == 1) {
      scanf("%lld", &k);
      st.Update2(1, 1, n, l, r, k);
    } else if (opt == 2) {
      scanf("%lld", &k);
      st.Update1(1, 1, n, l, r, k);
    } else {
      // for (int i = 1; i <= n; ++i)
      //   printf("%lld ", st.Query(1, 1, n, i, i));
      // printf("\n");
      printf("%lld\n", st.Query(1, 1, n, l, r));
    }
  }
  return 0;
}
