#include <algorithm>
#include <cmath>
#include <cstdio>

const int N = 4e6 + 10;

int n;
int a[N], ans[N];

int Gcd(int a, int b) {
  if (!b)
    return a;
  return Gcd(b, a % b);
}

// struct SegmentTree {
//   int t[N << 2];

// #define lc (rt << 1)
// #define rc (rt << 1 | 1)
// #define ls lc, l, mid
// #define rs rc, mid + 1, r

//   void PushUp(int rt) { t[rt] = Gcd(t[lc], t[rc]); }

//   void Build(int rt, int l, int r) {
//     if (l == r)
//       return t[rt] = a[l], void();
//     int mid = (l + r) >> 1;
//     Build(ls), Build(rs), PushUp(rt);
//   }

//   int Query(int rt, int l, int r, int ql, int qr) {
//     if (ql <= l && r <= qr)
//       return t[rt];
//     int mid = (l + r) >> 1, res = 0;
//     if (ql <= mid)
//       res = Gcd(Query(ls, ql, qr), res);
//     if (qr > mid)
//       res = Gcd(Query(rs, ql, qr), res);
//     return res;
//   }
// } st;

struct STable {
  int a[N][23];

  void Build() {
    for (int i = 1; i <= n; ++i)
      a[i][0] = ::a[i];
    for (int j = 1; j <= 22; ++j)
      for (int i = 1; i + (1 << j) - 1 <= n; ++i)
        a[i][j] = Gcd(a[i][j - 1], a[i + (1 << (j - 1))][j - 1]);
  }

  int Query(int l, int r) {
    int lo = log2(r - l + 1);
    return Gcd(a[l][lo], a[r - (1 << lo) + 1][lo]);
  }
} st;

int main() {
  int m, maxa = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), maxa = std::max(maxa, a[i]);
  // st.Build();
  // printf("%d\n", st.Query(2, 3));
  for (int l = 1; l <= n; ++l) {
    ++ans[a[l]];
    int r = l + 1;
    while (r <= n) {
      // printf("%d %d\n", l, r);
      // int t = Find(l, r), gcd = st.Query(l, r);
      // ++ans[gcd];
      // printf("%d %d %d %d\n", l, r, gcd, t);
      // r = t + 1;
    }
  }
  scanf("%d", &m);
  while (m--) {
    int a;
    scanf("%d", &a);
    printf("%d\n", ans[a]);
  }
  return 0;
}
