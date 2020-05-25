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
int n, X[N], Len, lst;
LL ans;
struct node {
  int l, r, h, typ;
} q[N];
bool cmp(const node& a, const node& b) {
  return a.h != b.h ? a.h < b.h : a.typ > b.typ;
}
#define lc (p << 1)
#define rc (p << 1 | 1)
int sum[N << 2], tim[N << 2], len[N << 2];
bool ls[N << 2], rs[N << 2];
void pushup(int p, int l, int r) {
  if (sum[p]) {
    len[p] = X[r + 1] - X[l];
    ls[p] = rs[p] = 1;
    tim[p] = 1;
  } else if (l == r) {
    ls[p] = rs[p] = 0;
    tim[p] = len[p] = 0;
  } else {
    tim[p] = tim[lc] + tim[rc];
    if (rs[lc] && ls[rc])
      --tim[p];
    len[p] = len[lc] + len[rc];
    ls[p] = ls[lc];
    rs[p] = rs[rc];
  }
}
void update(int ql, int qr, int l, int r, int p, int k) {
  if (ql <= l && r <= qr) {
    sum[p] += k;
    pushup(p, l, r);
    return;
  }
  int mid = (l + r) >> 1;
  if (mid >= ql)
    update(ql, qr, l, mid, lc, k);
  if (mid < qr)
    update(ql, qr, mid + 1, r, rc, k);
  pushup(p, l, r);
}
signed main() {
  n = rd();
  for (int i = 1; i <= n; ++i) {
    int xa = rd(), ya = rd(), xb = rd(), yb = rd();
    X[i * 2 - 1] = xa, X[i * 2] = xb;
    q[2 * i - 1].l = xa, q[2 * i - 1].r = xb, q[i * 2 - 1].h = ya,
              q[2 * i - 1].typ = 1;
    q[2 * i].l = xa, q[2 * i].r = xb, q[i * 2].h = yb, q[2 * i].typ = -1;
  }
  n <<= 1;
  sort(q + 1, q + n + 1, cmp);
  sort(X + 1, X + n + 1);
  Len = unique(X + 1, X + n + 1) - X - 1;
  for (int i = 1; i <= n; ++i) {
    int tl = lower_bound(X + 1, X + Len + 1, q[i].l) - X,
        tr = lower_bound(X + 1, X + Len + 1, q[i].r) - X - 1;
    update(tl, tr, 1, Len - 1, 1, q[i].typ);
    ans += abs(lst - len[1]), lst = len[1];
    ans += 2 * tim[1] * (q[i + 1].h - q[i].h);
  }
  printf("%lld\n", ans);
  return 0;
}