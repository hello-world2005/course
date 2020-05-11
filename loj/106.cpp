#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>

const int N = 5e4 + 10;
const int MAXN = 1e8;

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

  void PushUp(int rt) { t[rt].sze = t[lc(rt)].sze + t[rc(rt)].sze; }

  void Split(int rt, int v, int& rt1, int& rt2) {
    if (!rt) {
      rt1 = rt2 = 0;
      return;
    }
    if (t[rt].val <= v) {
      rt1 = rt;
      Split(rc(rt), v, rc(rt1), rt2);
    } else {
      rt2 = rt;
      Split(lc(rt), v, rt1, lc(rt2));
    }
    PushUp(rt);
  }

  int Merge(int rt1, int rt2) {
    if (!rt1 || !rt2)
      return rt1 + rt2;
    if (t[rt1].rnd < t[rt2].rnd) {
      rc(rt1) = Merge(lc(rt1), rt2);
      PushUp(rt1);
      return rt1;
    } else {
      lc(rt2) = Merge(rt1, rc(rt2));
      PushUp(rt2);
      return rt2;
    }
  }

  void Insert(int& rt, int v) {
    int rt1, rt2;
    Split(rt, v, rt1, rt2);
    rt = Merge(Merge(rt1, NewNode(v)), rt2);
  }

  void Delete(int& rt, int v) {
    int rt1, rt2, rt3;
    Split(rt, v, rt1, rt2);
    Split(rt1, v - 1, rt1, rt3);
    rt2 = Merge(lc(rt2), rc(rt2));
    rt = Merge(Merge(rt1, rt2), rt3);
  }

  int Kth(int rt, int k) {
    while (true) {
      if (t[lc(rt)].sze + 1 == k)
        return t[rt].val;
      if (t[lc(rt)].sze >= k)
        rt = lc(rt);
      else
        k -= t[lc(rt)].sze, rt = rc(rt);
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
    int res = Kth(rt1, t[rt1].sze);
    rt = Merge(rt1, rt2);
    return res;
  }

  int Nxt(int rt, int v) {
    int rt1, rt2;
    Split(rt, v, rt1, rt2);
    int res = Kth(rt2, 1);
    rt = Merge(rt1, rt2);
    return res;
  }
} fhq;

int ans;

struct SegmentTree {
  int t[N << 2];

#define lc (rt << 1)
#define rc (rt << 1 | 1)
#define ls lc, l, mid
#define rs rc, mid + 1, r

  void Insert(int rt, int l, int r, int p, int v) {
    fhq.Insert(rt, v);
    printf("%d\n", p);
    if (l == r)
      return;
    int mid = (l + r) >> 1;
    if (p <= mid)
      Insert(ls, p, v);
    else
      Insert(rs, p, v);
  }

  int Rank(int rt, int l, int r, int ql, int qr, int k) {
    if (l == ql && r == qr) {
      return fhq.Rank(rt, k);
    }
    int mid = (l + r) >> 1, res = 0;
    if (ql <= mid)
      res += Rank(ls, ql, qr, k);
    if (qr > mid)
      res += Rank(rs, ql, qr, k);
    return res;
  }

  int Kth(int ql, int qr, int k) {
    int l = 0, r = MAXN + 1;
    while (l < r) {
      int mid = (l + r) >> 1;
      if (Rank(1, 1, n, ql, qr, mid) < k)
        l = mid + 1;
      else
        r = mid;
    }
    return l - 1;
  }

  void Update(int rt, int l, int r, int p, int v) {
    fhq.Delete(rt, a[p]);
    fhq.Insert(rt, v);
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

  void Pre(int rt, int l, int r, int ql, int qr, int v, int& res) {
    if (l == ql && r == qr) {
      res = std::max(res, fhq.Pre(rt, v));
      return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid)
      Pre(ls, ql, qr, v, res);
    if (qr > mid)
      Pre(rs, ql, qr, v, res);
  }

  void Nxt(int rt, int l, int r, int ql, int qr, int v, int& res) {
    if (l == ql && r == qr) {
      res = std::min(res, fhq.Nxt(rt, v));
      return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid)
      Nxt(ls, ql, qr, v, res);
    if (qr > mid)
      Nxt(rs, ql, qr, v, res);
  }
} s;

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  for (int i = 1; i <= n; ++i)
    s.Insert(1, 1, n, i, a[i]);
  while (q--) {
    int opt, l, r, p, v;
    scanf("%d%d%d", &opt, &l, &r);
    if (opt == 1) {
      scanf("%d", &v);
      printf("%d\n", s.Rank(1, 1, n, l, r, v) + 1);
    } else if (opt == 2) {
      scanf("%d", &v);
      printf("%d\n", s.Kth(l, r, v));
    } else if (opt == 3) {
      scanf("%d%d", &p, &v);
      s.Update(1, 1, n, p, v);
    } else if (opt == 4) {
      scanf("%d", &v);
      int res = 0;
      s.Pre(1, 1, n, l, r, v, res);
      printf("%d\n", res);
    } else {
      scanf("%d", &v);
      int res = MAXN;
      s.Nxt(1, 1, n, l, r, v, res);
      printf("%d\n", res);
    }
  }
  return 0;
}
