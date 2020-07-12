#include <algorithm>
#include <cstdio>

#define int long long

const int N = 1e5 + 10;
const int INF = 1e9;

int n, m;
struct Edge {
  int v, nxt;

  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

int dep[N], sze[N], son[N], f[N];
int dfn[N], idx, top[N], a[N];
int cl[N];

void Dfs1(int u, int fa) {
  dep[u] = dep[f[u] = fa] + 1, cl[u] = sze[u] = 1;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    Dfs1(v, u), sze[u] += sze[v];
    if (sze[son[u]] < sze[v])
      son[u] = v;
  }
}

void Dfs2(int u, int tp) {
  top[u] = tp, a[dfn[u] = ++idx] = u;
  if (son[u])
    Dfs2(son[u], tp);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == f[u] || v == son[u])
      continue;
    Dfs2(v, v);
  }
}

struct SegmentTreeColor {
  int t[N << 2][2];

#define lc (rt << 1)
#define rc (rt << 1 | 1)
#define ls lc, l, mid
#define rs rc, mid + 1, r

  void PushUp(int rt) {
    t[rt][0] = std::max(t[lc][0], t[rc][0]),
    t[rt][1] = std::max(t[lc][1], t[rc][1]);
  }

  void Build(int rt, int l, int r) {
    t[rt][0] = -INF, t[rt][1] = r;
    if (l == r)
      return;
    int mid = (l + r) >> 1;
    Build(ls), Build(rs);
  }

  void Change(int rt, int l, int r, int p) {
    if (l == r)
      return std::swap(t[rt][0], t[rt][1]), void();
    int mid = (l + r) >> 1;
    if (p <= mid)
      Change(ls, p);
    else
      Change(rs, p);
    PushUp(rt);
  }

  int Query(int rt, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr)
      return t[rt][v];
    int mid = (l + r) >> 1, res = -INF;
    // if (ql <= mid)
    //   res = std::max(res, Query(ls, ql, qr, v));
    // if (qr > mid)
    //   res = std::max(res, Query(rs, ql, qr, v));
    // return res;
    if (qr > mid)
      res = Query(rs, ql, qr, v);
    if (res != -INF)
      return res;
    if (ql <= mid)
      res = Query(ls, ql, qr, v);
    return res;
  }
} col;

struct SegmentTreeValue {
  int a[N];
  int t[N << 2], lazy[N << 2];

#define lc (x << 1)
#define rc (x << 1 | 1)
#define ls lc, l, mid
#define rs rc, mid + 1, r

  void PushUp(int rt) { t[rt] = t[lc] + t[rc]; }

  void Build(int rt, int l, int r) {
    if (l == r)
      return t[rt] = a[l], void();
    int mid = (l + r) >> 1;
    Build(ls), Build(rs), PushUp(rt);
  }

  void PushDown(int rt, int l, int r) {
    if (lazy[rt]) {
      int mid = (l + r) >> 1;
      t[lc] += lazy[rt] * (mid - l + 1), t[rc] += lazy[rt] * (r - mid);
      lazy[lc] += lazy[rt], lazy[rc] += lazy[rt], lazy[rt] = 0;
    }
  }

  void Update(int rt, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr)
      return t[rt] += val * (r - l + 1), lazy[rt] += val, void();
    PushDown(rt, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid)
      Update(ls, ql, qr, val);
    else
      Update(rs, ql, qr, val);
    PushUp(rt);
  }

  int Query(int rt, int l, int r, int p) {
    if (l == r)
      return t[rt];
    PushDown(rt, l, r);
    int mid = (l + r) >> 1;
    if (p <= mid)
      return Query(ls, p);
    return Query(rs, p);
  }
} st[2];

int Find(int u, int opt) {
  while (top[u] != 1) {
    int now = col.Query(1, 1, n, dfn[top[u]], dfn[u], opt);
    if (now > 0)
      return a[now];
    u = f[top[u]];
  }
  u = col.Query(1, 1, n, 1, dfn[u], opt);
  if (u > 0)
    return a[u];
  return 1;
}

int Fa(int u, int v) {
  while (dep[f[top[u]]] > dep[v])
    u = f[top[u]];
  if (dep[top[u]] > dep[v])
    u = top[u];
  if (dep[u] == dep[v] + 1)
    return dfn[u];
  return dfn[v] + 1;
}

int Query(int u) {
  int v = Find(u, cl[u] ^ 1);
  if (cl[v] == cl[u])
    v = dfn[v];
  else
    v = Fa(u, v);
  // printf("%lld\n", cl[u]);
  return st[cl[u]].Query(1, 1, n, v);
}

void Change(int u, int v, int opt, int val) {
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]])
      std::swap(u, v);
    st[opt].Update(1, 1, n, dfn[top[u]], dfn[u], val);
    u = f[top[u]];
  }
  if (dep[u] > dep[v])
    std::swap(u, v);
  st[opt].Update(1, 1, n, dfn[u], dfn[v], val);
}

void Change(int u) {
  int now[2], k[2];
  for (int i = 0; i <= 1; ++i) {
    now[i] = st[i].Query(1, 1, n, dfn[u]);
    if (f[u])
      k[i] = Find(f[u], i);
  }
  if (f[u]) {
    Change(f[u], k[cl[u] ^ 1], cl[u], -now[cl[u]]);
    Change(f[u], k[cl[u]], cl[u] ^ 1, now[cl[u] ^ 1]);
  }
  printf("%lld %lld %lld %lld\n", k[0], k[1], now[0], now[1]);
  col.Change(1, 1, n, dfn[u]);
  cl[u] ^= 1;
}

signed main() {
  scanf("%lld", &n);
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%lld%lld", &u, &v);
    AddEdge(u, v), AddEdge(v, u);
  }
  Dfs1(1, 0), Dfs2(1, 1), col.Build(1, 1, n);
  for (int i = 1; i <= n; ++i)
    st[0].a[dfn[i]] = 1, st[1].a[dfn[i]] = sze[i];
  // st[0].Build(1, 1, n), st[1].Build(1, 1, n);
  scanf("%lld", &m);
  for (int i = 1, opt, u; i <= m; ++i) {
    scanf("%lld%lld", &opt, &u);
    if (opt == 0)
      printf("%lld\n", Query(u));
    else
      Change(u);
  }
  return 0;
}
