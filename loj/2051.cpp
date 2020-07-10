#include <algorithm>
#include <cstdio>
#include <stack>
#include <vector>

#define int long long

const int N = 1e5 + 10;

int n, q;
int a[N], l[N], r[N];

struct SegmentTree {
  struct Node {
    int sum, lazy;

    Node() : sum(0), lazy(0) {}
  } t[N << 2];

#define lc (rt << 1)
#define rc (rt << 1 | 1)
#define ls lc, l, mid
#define rs rc, mid + 1, r

  void PushUp(int rt) { t[rt].sum = t[lc].sum + t[rc].sum; }

  void PushDown(int rt, int l, int r) {
    if (t[rt].lazy) {
      int mid = (l + r) >> 1;
      t[lc].sum += t[rt].lazy * (mid - l + 1);
      t[rc].sum += t[rt].lazy * (r - mid);
      t[lc].lazy += t[rt].lazy;
      t[rc].lazy += t[rt].lazy;
      t[rt].lazy = 0;
    }
  }

  void Update(int rt, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
      t[rt].sum += (r - l + 1) * val;
      t[rt].lazy += val;
      return;
    }
    if (t[rt].lazy)
      PushDown(rt, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid)
      Update(ls, ql, qr, val);
    if (qr > mid)
      Update(rs, ql, qr, val);
    PushUp(rt);
  }

  int Query(int rt, int l, int r, int ql, int qr) {
    // printf("%lld %lld %lld %lld %lld\n", rt, l, r, ql, qr);
    if (ql <= l && r <= qr)
      return t[rt].sum;
    if (t[rt].lazy)
      PushDown(rt, l, r);
    int mid = (l + r) >> 1, res = 0;
    if (ql <= mid)
      res += Query(ls, ql, qr);
    if (qr > mid)
      res += Query(rs, ql, qr);
    return res;
  }
} ans, now;

int res[N];
int ql[N], qr[N];
std::vector<int> que[N];
std::vector<int> add[N], sub[N];

signed main() {
  scanf("%lld%lld", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]);
  std::stack<int> s;
  for (int i = 1; i <= n; ++i) {
    while (s.size() && a[s.top()] >= a[i])
      r[s.top()] = i, s.pop();
    s.push(i);
  }
  while (!s.empty())
    r[s.top()] = n + 1, s.pop();
  for (int i = n; i >= 1; --i) {
    while (s.size() && a[s.top()] > a[i])
      l[s.top()] = i, s.pop();
    s.push(i);
  }
  while (!s.empty())
    l[s.top()] = 0, s.pop();
  // for (int i = 1; i <= n; ++i)
  //   printf("%lld %lld\n", l[i], r[i]);
  for (int i = 1; i <= q; ++i) {
    scanf("%lld%lld", &ql[i], &qr[i]);
    que[qr[i]].push_back(i);
  }
  for (int i = 1; i <= n; ++i)
    add[i].push_back(i);
  for (int i = 1; i <= n; ++i)
    sub[r[i]].push_back(i);
  for (int i = 1; i <= n; ++i) {
    for (auto j : add[i]) {
      ans.Update(1, 1, n, l[j] + 1, j, (i - 1) * a[j]);
      now.Update(1, 1, n, l[j] + 1, j, a[j]);
    }
    for (auto j : sub[i]) {
      ans.Update(1, 1, n, l[j] + 1, j, (1 - i) * a[j]);
      now.Update(1, 1, n, l[j] + 1, j, -a[j]);
    }
    // printf("%lld\n", i);
    for (auto j : que[i]) {
      // printf("%lld %lld\n", now.Query(1, 1, n, ql[j], qr[j]),
      //        ans.Query(1, 1, n, ql[j], qr[j]));
      res[j] = i * now.Query(1, 1, n, ql[j], qr[j]) -
               ans.Query(1, 1, n, ql[j], qr[j]);
    }
  }
  for (int i = 1; i <= q; ++i)
    printf("%lld\n", res[i]);
  return 0;
}
