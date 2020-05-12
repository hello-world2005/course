#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>

const int N = 5e4 + 10;
const int INF = 1e8;

int n, q;
int a[N];

struct FhqTreap {
  struct Node {
    int val, rnd;
    int sze;
    int ch[2];

    Node() : val(0), rnd(rand()), sze(0) { ch[0] = ch[1] = 0; }
    Node(int _val) : val(_val), rnd(rand()), sze(1) { ch[0] = ch[1] = 0; }
  } t[N * 40];
  int cnt;

#define lc(rt) t[rt].ch[0]
#define rc(rt) t[rt].ch[1]

  int NewNode(int val) {
    t[++cnt] = Node(val);
    return cnt;
  }

  void PushUp(int rt) { t[rt].sze = t[lc(rt)].sze + t[rc(rt)].sze + 1; }

  void Split(int rt, int v, int& rt1, int& rt2) {
    // printf("%d %d %d %d\n", t[rt].val, v, rt1, rt2);
    if (!rt) {
      rt1 = rt2 = 0;
      return;
    }
    if (t[rt].val <= v) {
      rt1 = rt;
      Split(rc(rt), v, rc(rt), rt2);
    } else {
      rt2 = rt;
      Split(lc(rt), v, rt1, lc(rt));
    }
    PushUp(rt);
  }

  int Merge(int rt1, int rt2) {
    if (!rt1 || !rt2)
      return rt1 + rt2;
    if (t[rt1].rnd < t[rt2].rnd) {
      rc(rt1) = Merge(rc(rt1), rt2);
      PushUp(rt1);
      return rt1;
    } else {
      lc(rt2) = Merge(rt1, lc(rt2));
      PushUp(rt2);
      return rt2;
    }
  }

  void Insert(int& rt, int v) {
    int rt1, rt2;
    Split(rt, v, rt1, rt2);
    // printf("%d %d\n", rt, v);
    rt = Merge(Merge(rt1, NewNode(v)), rt2);
  }

  void Delete(int& rt, int v) {
    int rt1, rt2, rt3;
    Split(rt, v, rt1, rt3);
    Split(rt1, v - 1, rt1, rt2);
    rt2 = Merge(lc(rt2), rc(rt2));
    rt = Merge(Merge(rt1, rt2), rt3);
  }

  int Kth(int rt, int k, bool _DEBUG_ = false) {
    // if (_DEBUG_)
    //   printf("%d %d\n", rt, k);
    if (k == 0)
      return -INF;
    if (t[rt].sze == 0)
      return INF;
    while (true) {
      // printf("%d %d %d %d\n", rt, t[rt].sze, t[lc(rt)].sze, k);
      if (t[lc(rt)].sze + 1 == k)
        return t[rt].val;
      if (t[lc(rt)].sze >= k)
        rt = lc(rt);
      else
        k -= t[lc(rt)].sze + 1, rt = rc(rt);
    }
  }

  int Rank(int& rt, int v) {
    int rt1, rt2;
    Split(rt, v - 1, rt1, rt2);
    int res = t[rt1].sze;
    rt = Merge(rt1, rt2);
    return res;
  }

  int Pre(int rt, int v) {
    int rt1, rt2;
    Split(rt, v - 1, rt1, rt2);
    int res = Kth(rt1, t[rt1].sze, true);
    rt = Merge(rt1, rt2);
    return res;
  }

  int Nxt(int rt, int v) {
    int rt1, rt2;
    Split(rt, v, rt1, rt2);
    int res = Kth(rt2, 1);
    // printf("%d %d %d %d\n", v - 1, rt1, rt2, res);
    rt = Merge(rt1, rt2);
    return res;
  }

#undef lc
#undef rc
} fhq;

int ans;

struct SegmentTree {
  int ro[N << 2];

#define lc (rt << 1)
#define rc (rt << 1 | 1)
#define ls lc, l, mid
#define rs rc, mid + 1, r

  void Build(int rt, int l, int r) {
    for (int i = l; i <= r; ++i)
      fhq.Insert(ro[rt], a[i]);
    if (l == r)
      return;
    int mid = (l + r) >> 1;
    Build(ls);
    Build(rs);
  }

  int Rank(int rt, int l, int r, int ql, int qr, int k) {
    // printf("%d %d %d %d %d %d\n", rt, l, r, ql, qr, k);
    if (ql <= l && r <= qr) {
      // printf("%d %d %d %d\n", rt, l, r, fhq.Rank(ro[rt], k));
      return fhq.Rank(ro[rt], k);
    }
    int mid = (l + r) >> 1, res = 0;
    if (ql <= mid)
      res += Rank(ls, ql, qr, k);
    if (qr > mid)
      res += Rank(rs, ql, qr, k);
    return res;
  }

  int Kth(int ql, int qr, int k) {
    int l = 0, r = INF + 1, res;
    while (l <= r) {
      int mid = (l + r) >> 1;
      // printf("%d\n", mid);
      if (Rank(1, 1, n, ql, qr, mid) < k)
        l = mid + 1, res = mid;
      else
        r = mid - 1;
    }
    return res;
  }

  void Update(int rt, int l, int r, int p, int v) {
    fhq.Delete(ro[rt], a[p]);
    fhq.Insert(ro[rt], v);
    if (l == r) {
      a[p] = v;
      return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
      Update(ls, p, v);
    else
      Update(rs, p, v);
  }

  int Pre(int rt, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr)
      return fhq.Pre(ro[rt], v);
    int mid = (l + r) >> 1, res = -INF;
    if (ql <= mid)
      res = std::max(res, Pre(ls, ql, qr, v));
    if (qr > mid)
      res = std::max(res, Pre(rs, ql, qr, v));
    return res;
  }

  int Nxt(int rt, int l, int r, int ql, int qr, int v) {
    // printf("%d %d %d %d %d %d\n", rt, l, r, ql, qr, v);
    if (ql <= l && r <= qr)
      return fhq.Nxt(ro[rt], v);
    int mid = (l + r) >> 1, res = INF;
    if (ql <= mid)
      res = std::min(res, Nxt(ls, ql, qr, v));
    if (qr > mid)
      res = std::min(res, Nxt(rs, ql, qr, v));
    return res;
  }

#undef lc
#undef rc
#undef ls
#undef rs
} s;

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  s.Build(1, 1, n);
  while (q--) {
    int opt, l, r, v;
    scanf("%d%d%d", &opt, &l, &r);
    if (opt == 1) {
      scanf("%d", &v);
      printf("%d\n", s.Rank(1, 1, n, l, r, v) + 1);
    } else if (opt == 2) {
      scanf("%d", &v);
      printf("%d\n", s.Kth(l, r, v));
    } else if (opt == 3) {
      s.Update(1, 1, n, l, r);
    } else if (opt == 4) {
      scanf("%d", &v);
      printf("%d\n", s.Pre(1, 1, n, l, r, v));
    } else {
      scanf("%d", &v);
      printf("%d\n", s.Nxt(1, 1, n, l, r, v));
    }
  }
  return 0;
}
