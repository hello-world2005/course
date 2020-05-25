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
const int N = 60010;
int c, s, r;
#define lc p << 1
#define rc p << 1 | 1
int val[N << 2], tag[N << 2];
void pushup(int p) {
  val[p] = min(val[lc], val[rc]);
}
void build(int l, int r, int p) {
  if (l == r)
    return void(val[p] = s);
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
  int mid = (l + r) >> 1, res = s;
  if (mid >= ql)
    res = min(res, query(ql, qr, l, mid, lc));
  if (mid < qr)
    res = min(res, query(ql, qr, mid + 1, r, rc));
  return res;
}
signed main() {
  c = rd(), s = rd(), r = rd();
  build(1, c, 1);
  for (int i = 1; i <= r; ++i) {
    int x = rd(), y = rd(), z = rd();
    if (query(x, y - 1, 1, c, 1) >= z) {
      update(x, y - 1, 1, c, 1, -z);
      putchar('T'), putchar('\n');
    } else {
      putchar('N'), putchar('\n');
    }
  }
  return 0;
}