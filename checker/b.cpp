#include<cstdio>
#include <algorithm>
#include <cstring>

#define read() Read<int>()
namespace pb_ds {
namespace io {
const int MaxBuff = 1 << 15;
const int Output = 1 << 23;
char B[MaxBuff], *S = B, *T = B;
#define getc() \
  ((S == T) && (T = (S = B) + fread(B, 1, MaxBuff, stdin), S == T) ? 0 : *S++)
char Out[Output], *iter = Out;
inline void flush() {
  fwrite(Out, 1, iter - Out, stdout);
  iter = Out;
}
}  // namespace io
template <class Type>
inline Type Read() {
  using namespace io;
  register char ch;
  register Type ans = 0;
  register bool neg = 0;
  while (ch = getc(), (ch < '0' || ch > '9') && ch != '-')
    ;
  ch == '-' ? neg = 1 : ans = ch - '0';
  while (ch = getc(), '0' <= ch && ch <= '9')
    ans = ans * 10 + ch - '0';
  return neg ? -ans : ans;
}
template <class Type>
inline void Print(register Type x, register char ch = '\n') {
  using namespace io;
  if (!x)
    *iter++ = '0';
  else {
    if (x < 0)
      *iter++ = '-', x = -x;
    static int s[100];
    register int t = 0;
    while (x)
      s[++t] = x % 10, x /= 10;
    while (t)
      *iter++ = '0' + s[t--];
  }
  *iter++ = ch;
}
}  // namespace pb_ds
using namespace pb_ds;
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
const int inf = 1e9;
#define mid (l + r >> 1)
#define ls (x << 1)
#define rs (ls | 1)
namespace seg_tree {
int fr[N << 2][2];
inline void pushup(int x) {
  fr[x][0] = max(fr[ls][0], fr[rs][0]);
  fr[x][1] = max(fr[ls][1], fr[rs][1]);
}
void build(int x, int l, int r) {
  fr[x][0] = -inf, fr[x][1] = r;
  if (l == r)
    return;
  build(ls, l, mid), build(rs, mid + 1, r);
}
void update(int x, int l, int r, int pos) {
  if (l == r) {
    swap(fr[x][0], fr[x][1]);
    return;
  }
  if (pos <= mid)
    update(ls, l, mid, pos);
  else
    update(rs, mid + 1, r, pos);
  pushup(x);
}
int query(int x, int l, int r, int L, int R, int opt) {
  if (L <= l && r <= R)
    return fr[x][opt];
  int res = -inf;
  if (R > mid)
    res = query(rs, mid + 1, r, L, R, opt);
  if (res != -inf)
    return res;
  if (L <= mid)
    res = query(ls, l, mid, L, R, opt);
  return res;
}
}  // namespace seg_tree
using namespace seg_tree;
struct seg {
  int add[N << 2], val[N];
  inline void Add(int x, int l, int r, int k) {
    if (l == r)
      val[l] += k;
    else
      add[x] += k;
  }
  inline void pushdown(int x, int l, int r) {
    if (add[x]) {
      Add(ls, l, mid, add[x]);
      Add(rs, mid + 1, r, add[x]);
      add[x] = 0;
    }
  }
  void update(int x, int l, int r, int L, int R, int k) {
    if (L <= l && r <= R) {
      Add(x, l, r, k);
      return;
    }
    pushdown(x, l, r);
    if (L <= mid)
      update(ls, l, mid, L, R, k);
    if (R > mid)
      update(rs, mid + 1, r, L, R, k);
  }
  int query(int x, int l, int r, int pos) {
    if (l == r)
      return val[l];
    pushdown(x, l, r);
    if (pos <= mid)
      return query(ls, l, mid, pos);
    return query(rs, mid + 1, r, pos);
  }
} s[2];
int n, m, tot;
int dfn[N], fa[N], sz[N];
int son[N], dep[N], top[N];
int tp[N], rk[N];
struct edge {
  int next, to;
} a[N << 1];
int head[N], cnt;
inline void add(int u, int v) {
  a[++cnt].to = v;
  a[cnt].next = head[u];
  head[u] = cnt;
}
void dfs1(int x) {
  dep[x] = dep[fa[x]] + 1;
  sz[x] = tp[x] = 1;
  for (int i = head[x]; i; i = a[i].next) {
    int y = a[i].to;
    if (y == fa[x])
      continue;
    fa[y] = x, dfs1(y), sz[x] += sz[y];
    if (sz[son[x]] < sz[y])
      son[x] = y;
  }
}
void dfs2(int x) {
  if (x ^ son[fa[x]])
    top[x] = x;
  else
    top[x] = top[fa[x]];
  rk[dfn[x] = ++tot] = x;
  if (son[x])
    dfs2(son[x]);
  for (int i = head[x]; i; i = a[i].next) {
    int y = a[i].to;
    if (y == fa[x] || y == son[x])
      continue;
    dfs2(y);
  }
}
inline int find(int x, int opt) {
  while (top[x] ^ 1) {
    int now = query(1, 1, n, dfn[top[x]], dfn[x], opt);
    if (now > 0)
      return rk[now];
    x = fa[top[x]];
  }
  x = query(1, 1, n, 1, dfn[x], opt);
  if (x > 0)
    return rk[x];
  return 1;
}
inline void work(int u, int v, int opt, int w) {
  while (top[u] ^ top[v]) {
    if (dep[top[u]] < dep[top[v]])
      swap(u, v);
    s[opt].update(1, 1, n, dfn[top[u]], dfn[u], w);
    u = fa[top[u]];
  }
  if (dep[u] > dep[v])
    swap(u, v);
  s[opt].update(1, 1, n, dfn[u], dfn[v], w);
}
inline int get_fa(int x, int u) {
  while (dep[fa[top[x]]] > dep[u])
    x = fa[top[x]];
  if (dep[top[x]] > dep[u])
    x = top[x];
  if (dep[x] == dep[u] + 1)
    return dfn[x];
  return dfn[u] + 1;
}
int main() {
  n = read();
  for (int i = 1; i < n; ++i) {
    int u = read(), v = read();
    add(u, v), add(v, u);
  }
  dfs1(1), dfs2(1);
  for (int i = 1; i <= n; ++i) {
    s[1].val[dfn[i]] = sz[i];
    s[0].val[dfn[i]] = 1;
  }
  build(1, 1, n);
  m = read();
  while (m--) {
    int opt = read(), x = read();
    if (!opt) {
      int y = find(x, tp[x] ^ 1);
      if (tp[y] == tp[x])
        y = dfn[y];
      else
        y = get_fa(x, y);
      Print(s[tp[x]].query(1, 1, n, y));
    } else {
      int now[2], f[2];
      for (int i = 0; i <= 1; ++i) {
        now[i] = s[i].query(1, 1, n, dfn[x]);
        if (fa[x])
          f[i] = find(fa[x], i), Print(33211);
      }
      if (fa[x]) {
        work(fa[x], f[tp[x] ^ 1], tp[x], -now[tp[x]]);
        work(fa[x], f[tp[x]], tp[x] ^ 1, now[tp[x] ^ 1]);
      }
      Print(f[0], ' '), Print(f[1], ' '), Print(now[0], ' '), Print(now[1]);
      update(1, 1, n, dfn[x]);
      tp[x] ^= 1;
    }
  }
  io::flush();
  return 0;
}