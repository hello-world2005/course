#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline int rd() {
  int x = 0, f = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (isdigit(ch))
    x = x * 10 + (ch ^ 48), ch = getchar();
  return x * f;
}
const int N = 100010;
int a[N], n, m, ans;
struct QUE {
  int l, r;
} q[N];
bool cmp(const QUE& a, const QUE& b) {
  return a.r != b.r ? a.r < b.r : a.l > b.l;
}
#define lc p << 1
#define rc p << 1 | 1
int val[N << 2], tag[N << 2];
void pushup(int p) {
  val[p] = min(val[lc], val[rc]);
}
void build(int l, int r, int p) {
  if (l == r)
    return void(val[p] = a[l]);
  int mid = (l + r) >> 1;
  build(l, mid, lc), build(mid + 1, r, rc);
  pushup(p);
}
void pushdown(int p, int l, int r) {
  if (!tag[p])
    return;
  val[lc] = val[lc] + tag[p];
  val[rc] = val[rc] + tag[p];
  tag[lc] = tag[lc] + tag[p];
  tag[rc] = tag[rc] + tag[p];
  tag[p] = 0;
}
void update(int ql, int qr, int l, int r, int p, int k) {
  if (ql <= l && r <= qr) {
    tag[p] = tag[p] + k;
    val[p] = val[p] + k;
    return;
  }
  pushdown(p, l, r);
  int mid = (l + r) >> 1;
  if (mid >= ql)
    update(ql, qr, l, mid, lc, k);
  if (mid < qr)
    update(ql, qr, mid + 1, r, rc, k);
  pushup(p);
}
int query(int ql, int qr, int l, int r, int p) {
  if (ql <= l && r <= qr)
    return val[p];
  pushdown(p, l, r);
  int mid = (l + r) >> 1, res = N;
  if (mid >= ql)
    res = min(res, query(ql, qr, l, mid, lc));
  if (mid < qr)
    res = min(res, query(ql, qr, mid + 1, r, rc));
  return res;
}
signed main() {
  n = rd(), m = rd();
  for (int i = 1; i <= n; ++i)
    a[i] = rd();
  build(1, n, 1);
  for (int i = 1; i <= m; ++i)
    q[i].l = rd(), q[i].r = rd();
  sort(q + 1, q + m + 1, cmp);
  for (int i = 1; i <= m; ++i)
    if (query(q[i].l, q[i].r, 1, n, 1) > 0)
      update(q[i].l, q[i].r, 1, n, 1, -1), ++ans;
  printf("%d\n", ans);
  return 0;
}