#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;

const int N = 2e5 + 10;

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

struct SegmentTree {
  struct Node {
    ll tag1, tag2, tag3;
  } t[N << 2];

#define lc (rt << 1)
#define rc (rt << 1 | 1)
#define ls lc, l, mid
#define rs rc, mid + 1, r

  void PushDown(int rt) {
    if (t[rt].tag3) {
      t[lc].tag3 += t[rt].tag3, t[rc].tag3 += t[rt].tag3;
      t[lc].tag2 += t[rt].tag3 * t[lc].tag1 + t[rt].tag2,
          t[rc].tag2 += t[rt].tag3 * t[rc].tag1 + t[rt].tag2;
    }
    if (t[rt].tag1)
      t[lc].tag1 += t[rt].tag1, t[rc].tag1 += t[rt].tag1;
    t[rt].tag1 = t[rt].tag2 = t[rt].tag3 = 0;
  }

  void Update(int rt, int l, int r, int ql, int qr, int k) {
    if (ql <= l && r <= qr) {
      t[rt].tag1 += k;
      return;
    }
    PushDown(rt);
    int mid = (l + r) >> 1;
    if (ql <= mid)
      Update(ls, ql, qr, k);
    if (qr > mid)
      Update(rs, ql, qr, k);
  }

  void Add(int rt, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
      t[rt].tag2 += t[rt].tag1;
      ++t[rt].tag3;
      return;
    }
    PushDown(rt);
    int mid = (l + r) >> 1;
    if (ql <= mid)
      Add(ls, ql, qr);
    if (qr > mid)
      Add(rs, ql, qr);
  }

  ll a[N];

  void PushDown(int rt, int l, int r) {
    if (l == r)
      return void(a[l] = t[rt].tag2);
    PushDown(rt);
    int mid = (l + r) >> 1;
    PushDown(ls), PushDown(rs);
  }
} st;

int sze[N], son[N], dfn[N], idx, tp[N], fa[N];

void Dfs1(int now, int fa) {
  ::fa[now] = fa;
  sze[now] = 1;
  for (int i = head[now]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    Dfs1(v, now);
    sze[now] += sze[v];
    if (sze[v] > sze[son[now]])
      son[now] = v;
  }
}

void Dfs2(int now, int fa, int tp) {
  ::tp[now] = tp;
  dfn[now] = ++idx;
  if (son[now])
    Dfs2(son[now], now, tp);
  for (int i = head[now]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa || v == son[now])
      continue;
    Dfs2(v, now, v);
  }
}

ll ans[N];

void Update(int x, int k) {
  while (x)
    st.Update(1, 1, n, dfn[tp[x]], dfn[x], k), x = fa[tp[x]];
}

void Add(int x) {
  while (x)
    st.Add(1, 1, n, dfn[tp[x]], dfn[x]), x = fa[tp[x]];
}

void Dfs3(int now, int fa) {
  ans[now] = st.a[dfn[now]];
  for (int i = head[now]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    ans[v] = st.a[dfn[v]], ans[now] -= ans[v];
    Dfs3(v, now);
  }
}

int col[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &col[i]);
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v), AddEdge(v, u);
  }
  Dfs1(1, 0), Dfs2(1, 0, 1);
  for (int i = 1; i <= n; ++i)
    if (col[i])
      Update(i, i);
  for (int i = 1, opt, x; i <= m; ++i) {
    scanf("%d%d", &opt, &x);
    if (opt == 1)
      Add(x);
    else
      col[x] ^= 1, Update(x, col[x] ? x : -x);
  }
  st.PushDown(1, 1, n);
  Dfs3(1, 0);
  for (int i = 1; i <= n; ++i)
    printf("%lld\n", ans[i]);
  return 0;
}
