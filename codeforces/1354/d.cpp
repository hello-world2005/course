#include <cstdio>

const int N = 1e6 + 10;

int n, q;
int a[N];

struct SegmentTree {
  struct Node {
    int val;
  } t[N << 2];

#define lc (rt << 1)
#define rc (rt << 1 | 1)
#define ls lc, l, mid
#define rs rc, mid + 1, r

  void Add(int rt, int l, int r, int p, int v) {
    t[rt].val += v;
    if (l == r)
      return;
    int mid = (l + r) >> 1;
    if (p <= mid)
      Add(ls, p, v);
    else
      Add(rs, p, v);
  }

  int Find(int rt, int l, int r, int k) {
    if (l == r)
      return l;
    int mid = (l + r) >> 1;
    if (k <= t[lc].val)
      return Find(ls, k);
    else
      return Find(rs, k - t[lc].val);
  }

  int GetAns(int rt, int l, int r) {
    if (l == r)
      return l;
    int mid = (l + r) >> 1;
    if (t[lc].val)
      return GetAns(ls);
    else
      return GetAns(rs);
  }
} st;

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), st.Add(1, 1, n, a[i], 1);
  // int l = 1, r = n, ans;
  // while (l <= r) {
  //   int mid = (l + r) >> 1;
  // }
  while (q--) {
    int k;
    scanf("%d", &k);
    if (k < 0) {
      k = -k;
      st.Add(1, 1, n, st.Find(1, 1, n, k), -1);
    } else {
      st.Add(1, 1, n, k, 1);
    }
  }
  if (st.t[1].val == 0)
    return printf("0\n"), 0;
  printf("%d\n", st.GetAns(1, 1, n));
  return 0;
}
