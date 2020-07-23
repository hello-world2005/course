// #include <algorithm>
// #include <cstdio>
// #include <cstdlib>
// #include <ctime>

// const int N = 3e5 + 10;
// const int INF = 2e9;

// int n, q;
// int a[N];

// struct FhqTreap {
//   int rub[N * 40], top = 0;
//   struct Node {
//     int val, rnd;
//     int sze;
//     int ch[2];

//     Node() : val(0), rnd(rand()), sze(0) { ch[0] = ch[1] = 0; }
//     Node(int _val) : val(_val), rnd(rand()), sze(1) { ch[0] = ch[1] = 0; }
//   } t[N * 20];
//   int cnt;

// #define lc(rt) t[rt].ch[0]
// #define rc(rt) t[rt].ch[1]

//   int NewNode(int val) {
//     int zzc = top ? rub[top--] : ++cnt;
//     t[zzc] = Node(val);
//     return zzc;
//   }

//   void PushUp(int rt) { t[rt].sze = t[lc(rt)].sze + t[rc(rt)].sze + 1; }

//   void Split(int rt, int v, int& rt1, int& rt2) {
//     // printf("%d %d %d %d\n", t[rt].val, v, rt1, rt2);
//     if (!rt) {
//       rt1 = rt2 = 0;
//       return;
//     }
//     if (t[rt].val <= v) {
//       rt1 = rt;
//       Split(rc(rt), v, rc(rt), rt2);
//     } else {
//       rt2 = rt;
//       Split(lc(rt), v, rt1, lc(rt));
//     }
//     PushUp(rt);
//   }

//   int Merge(int rt1, int rt2) {
//     if (!rt1 || !rt2)
//       return rt1 + rt2;
//     if (t[rt1].rnd < t[rt2].rnd) {
//       rc(rt1) = Merge(rc(rt1), rt2);
//       PushUp(rt1);
//       return rt1;
//     } else {
//       lc(rt2) = Merge(rt1, lc(rt2));
//       PushUp(rt2);
//       return rt2;
//     }
//   }

//   void Insert(int& rt, int v) {
//     int rt1, rt2;
//     Split(rt, v, rt1, rt2);
//     // printf("%d %d\n", rt, v);
//     rt = Merge(Merge(rt1, NewNode(v)), rt2);
//   }

//   void Delete(int& rt, int v) {
//     int rt1, rt2, rt3;
//     Split(rt, v, rt1, rt3);
//     Split(rt1, v - 1, rt1, rt2);
//     rub[++top] = rt2;
//     rt2 = Merge(lc(rt2), rc(rt2));
//     rt = Merge(Merge(rt1, rt2), rt3);
//   }

//   int Kth(int rt, int k, bool _DEBUG_ = false) {
//     // if (_DEBUG_)
//     //   printf("%d %d\n", rt, k);
//     if (k == 0)
//       return -INF;
//     if (t[rt].sze == 0)
//       return INF;
//     while (true) {
//       // printf("%d %d %d %d\n", rt, t[rt].sze, t[lc(rt)].sze, k);
//       if (t[lc(rt)].sze + 1 == k)
//         return t[rt].val;
//       if (t[lc(rt)].sze >= k)
//         rt = lc(rt);
//       else
//         k -= t[lc(rt)].sze + 1, rt = rc(rt);
//     }
//   }

//   int Rank(int& rt, int v) {
//     int rt1, rt2;
//     Split(rt, v - 1, rt1, rt2);
//     int res = t[rt1].sze;
//     rt = Merge(rt1, rt2);
//     return res;
//   }

//   int Pre(int rt, int v) {
//     int rt1, rt2;
//     Split(rt, v - 1, rt1, rt2);
//     int res = Kth(rt1, t[rt1].sze, true);
//     rt = Merge(rt1, rt2);
//     return res;
//   }

//   int Nxt(int rt, int v) {
//     int rt1, rt2;
//     Split(rt, v, rt1, rt2);
//     int res = Kth(rt2, 1);
//     // printf("%d %d %d %d\n", v - 1, rt1, rt2, res);
//     rt = Merge(rt1, rt2);
//     return res;
//   }

// #undef lc
// #undef rc
// } fhq;

// int ans;

// struct SegmentTree {
//   int ro[N << 2];

// #define lc (rt << 1)
// #define rc (rt << 1 | 1)
// #define ls lc, l, mid
// #define rs rc, mid + 1, r

//   void Build(int rt, int l, int r) {
//     for (int i = l; i <= r; ++i)
//       fhq.Insert(ro[rt], a[i]);
//     if (l == r)
//       return;
//     int mid = (l + r) >> 1;
//     Build(ls);
//     Build(rs);
//   }

//   int Rank(int rt, int l, int r, int ql, int qr, int k) {
//     // printf("%d %d %d %d %d %d\n", rt, l, r, ql, qr, k);
//     if (ql <= l && r <= qr) {
//       // printf("%d %d %d %d\n", rt, l, r, fhq.Rank(ro[rt], k));
//       return fhq.Rank(ro[rt], k);
//     }
//     int mid = (l + r) >> 1, res = 0;
//     if (ql <= mid)
//       res += Rank(ls, ql, qr, k);
//     if (qr > mid)
//       res += Rank(rs, ql, qr, k);
//     return res;
//   }

//   int Kth(int ql, int qr, int k) {
//     int l = 0, r = INF + 1, res;
//     while (l <= r) {
//       int mid = (l + r) >> 1;
//       // printf("%d\n", mid);
//       if (Rank(1, 1, n, ql, qr, mid) < k)
//         l = mid + 1, res = mid;
//       else
//         r = mid - 1;
//     }
//     return res;
//   }

//   void Update(int rt, int l, int r, int p, int v) {
//     fhq.Delete(ro[rt], a[p]);
//     fhq.Insert(ro[rt], v);
//     if (l == r) {
//       a[p] = v;
//       return;
//     }
//     int mid = (l + r) >> 1;
//     if (p <= mid)
//       Update(ls, p, v);
//     else
//       Update(rs, p, v);
//   }

//   int Pre(int rt, int l, int r, int ql, int qr, int v) {
//     if (ql <= l && r <= qr)
//       return fhq.Pre(ro[rt], v);
//     int mid = (l + r) >> 1, res = -INF;
//     if (ql <= mid)
//       res = std::max(res, Pre(ls, ql, qr, v));
//     if (qr > mid)
//       res = std::max(res, Pre(rs, ql, qr, v));
//     return res;
//   }

//   int Nxt(int rt, int l, int r, int ql, int qr, int v) {
//     // printf("%d %d %d %d %d %d\n", rt, l, r, ql, qr, v);
//     if (ql <= l && r <= qr)
//       return fhq.Nxt(ro[rt], v);
//     int mid = (l + r) >> 1, res = INF;
//     if (ql <= mid)
//       res = std::min(res, Nxt(ls, ql, qr, v));
//     if (qr > mid)
//       res = std::min(res, Nxt(rs, ql, qr, v));
//     return res;
//   }

// #undef lc
// #undef rc
// #undef ls
// #undef rs
// } s;

// int main() {
//   scanf("%d%d", &n, &q);
//   for (int i = 1; i <= n; ++i)
//     scanf("%d", &a[i]);
//   s.Build(1, 1, n);
//   while (q--) {
//     int l, r, k;
//     scanf("%d%d%d", &l, &r, &k);
//     printf("%d\n", s.Kth(l, r, k));
//   }
//   return 0;
// }

#include <algorithm>
#include <cstdio>

const int N = 3e5 + 10;

int rt[N];
int a[N], b[N];
struct SegmentTree {
  int ch[N * 40][2], v[N * 40], cnt = 0;

  void Build(int& rt, int l, int r) {
    rt = ++cnt;
    if (l == r)
      return v[rt] = b[l], void();
    int mid = (l + r) >> 1;
    Build(ch[rt][0], l, mid), Build(ch[rt][1], mid + 1, r);
  }

  void Update(int& rt, int p, int l, int r, int val) {
    rt = ++cnt;
    ch[rt][0] = ch[p][0], ch[rt][1] = ch[p][1], v[rt] = v[p] + 1;
    if (l == r)
      return;
    int mid = (l + r) >> 1;
    if (val <= mid)
      Update(ch[rt][0], ch[p][0], l, mid, val);
    else
      Update(ch[rt][1], ch[p][1], mid + 1, r, val);
  }

  int Query(int rt, int p, int l, int r, int k) {
    int t = v[ch[rt][0]] - v[ch[p][0]];
    if (l == r)
      return l;
    int mid = (l + r) >> 1;
    if (k <= t)
      return Query(ch[rt][0], ch[p][0], l, mid, k);
    else
      return Query(ch[rt][1], ch[p][1], mid + 1, r, k - t);
  }
} st;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), b[i] = a[i];
  std::sort(b + 1, b + n + 1);
  int _n = std::unique(b + 1, b + n + 1) - b - 1;
  st.Build(rt[0], 1, _n);
  for (int i = 1; i <= n; ++i) {
    int id = std::lower_bound(b + 1, b + _n + 1, a[i]) - b;
    st.Update(rt[i], rt[i - 1], 1, _n, id);
  }
  while (m--) {
    int l, r, k;
    scanf("%d%d%d", &l, &r, &k);
    printf("%d\n", b[st.Query(rt[r], rt[l - 1], 1, _n, k)]);
  }
  return 0;
}
