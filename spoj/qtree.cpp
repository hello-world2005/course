#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 10;

int n;
int a[N];
int _u[N], _v[N], _w[N];
struct Edge {
  int v, w, nxt;

  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int pos[N];

struct SegmentTree {
  struct Node {
    int maxn;
  } t[N << 2];

#define lc (rt << 1)
#define rc (rt << 1 | 1)
#define ls lc, l, mid
#define rs rc, mid + 1, r

  void PushUp(int rt) { t[rt].maxn = std::max(t[lc].maxn, t[rc].maxn); }

  void Build(int rt, int l, int r) {
    if (l == r) {
      t[rt].maxn = a[pos[l]];
      return;
    }
    int mid = (l + r) >> 1;
    Build(ls);
    Build(rs);
    PushUp(rt);
  }

  void Add(int rt, int l, int r, int p, int v) {
    if (l == r) {
      t[rt].maxn = v;
      return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
      Add(ls, p, v);
    else
      Add(rs, p, v);
    PushUp(rt);
  }

  int Query(int rt, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
      return t[rt].maxn;
    int mid = (l + r) >> 1, res = 0;
    if (ql <= mid)
      res = std::max(res, Query(ls, ql, qr));
    if (qr > mid)
      res = std::max(res, Query(rs, ql, qr));
    return res;
  }
} st;

int dep[N], sze[N], son[N], f[N];
int dfn[N], idx, top[N];

void Dfs1(int u, int fa) {
  f[u] = fa;
  dep[u] = dep[fa] + 1;
  sze[u] = 1;
  top[u] = son[u] = 0;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    a[v] = e[i].w;
    Dfs1(v, u);
    sze[u] += sze[v];
    if (sze[son[u]] < sze[v])
      son[u] = v;
  }
}

void Dfs2(int u, int tp) {
  top[u] = tp;
  dfn[u] = ++idx;
  pos[idx] = u;
  if (son[u])
    Dfs2(son[u], tp);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == f[u] || v == son[u])
      continue;
    Dfs2(v, v);
  }
}

void Update(int u, int val) {
  int t = u, v;
  u = _u[t], v = _v[t];
  if (f[v] == u)
    std::swap(u, v);
  st.Add(1, 1, n, dfn[u], val);
}

int Query(int u, int v) {
  int res = 0;
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]])
      std::swap(u, v);
    res = std::max(res, st.Query(1, 1, n, dfn[top[u]], dfn[u]));
    u = f[top[u]];
  }
  if (dep[u] < dep[v])
    std::swap(u, v);
  if (u == v)
    return res;
  res = std::max(res, st.Query(1, 1, n, dfn[v] + 1, dfn[u]));
  return res;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    memset(head, 0, sizeof(head));
    edge_cnt = idx = 0;
    scanf("%d", &n);
    for (int i = 1, u, v, w; i < n; ++i) {
      scanf("%d%d%d", &u, &v, &w);
      AddEdge(u, v, w);
      AddEdge(v, u, w);
      _u[i] = u, _v[i] = v, _w[i] = w;
    }
    Dfs1(1, 0);
    Dfs2(1, 1);
    st.Build(1, 1, n);
    while (true) {
      char opt[10];
      int u, v;
      scanf("%s", opt);
      if (opt[0] == 'C') {
        scanf("%d%d", &u, &v);
        Update(u, v);
      } else if (opt[0] == 'Q') {
        scanf("%d%d", &u, &v);
        printf("%d\n", Query(u, v));
      } else {
        break;
      }
    }
  }
  return 0;
}
