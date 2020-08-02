#include <algorithm>
#include <cstdio>
#include <cstring>

#define int long long

const int N = 1e5 + 10;
const int INF = 2e9;

int n, m;
int a[N];
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

// Heavy Light

int sze[N], son[N], in[N], ou[N], idx, tp[N], fa[N], bel[N];

void Dfs1(int u, int fa) {
  ::fa[u] = fa, sze[u] = 1;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    Dfs1(v, u);
    sze[u] += sze[v];
    if (sze[v] > sze[son[u]])
      son[u] = v;
  }
}

void Dfs2(int u, int fa, int tp) {
  ::tp[u] = tp, in[u] = ++idx, ou[tp] = idx, bel[idx] = u;
  if (son[u])
    Dfs2(son[u], u, tp);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa || v == son[u])
      continue;
    Dfs2(v, u, v);
  }
}

struct Matrix {
  int a[2][2];

  Matrix() { memset(a, 0, sizeof(a)); }

  void Init() { a[0][0] = a[0][1] = a[1][0] = a[1][1] = -INF; }

  Matrix operator*(const Matrix& rhs) {
    Matrix res;
    res.Init();
    for (int i = 0; i <= 1; ++i)
      for (int j = 0; j <= 1; ++j)
        for (int k = 0; k <= 1; ++k)
          res.a[i][j] = std::max(res.a[i][j], a[i][k] + rhs.a[k][j]);
    return res;
  }

  void Print() { printf("%d %d %d %d\n", a[0][0], a[0][1], a[1][0], a[1][1]); }
};

int dp[N][2], ldp[N][2];  // both, only light
Matrix mat[N];

struct SegmentTree {
#define lc (rt << 1)
#define rc (rt << 1 | 1)
#define ls lc, l, mid
#define rs rc, mid + 1, r

  Matrix t[N << 2];

  void PushUp(int rt) { t[rt] = t[lc] * t[rc]; }

  void Build(int rt, int l, int r) {
    if (l == r) {
      mat[bel[l]].a[0][0] = ldp[bel[l]][0],
      mat[bel[l]].a[0][1] = ldp[bel[l]][0],
      mat[bel[l]].a[1][0] = ldp[bel[l]][1], mat[bel[l]].a[1][1] = -INF;
      t[rt] = mat[bel[l]];
      // printf("%d: ", rt), t[rt].Print();
      return;
    }
    int mid = (l + r) >> 1;
    Build(ls), Build(rs);
    PushUp(rt);
  }

  void Update(int rt, int l, int r, int p) {
    if (l == r)
      return t[rt] = mat[bel[l]], void();
    int mid = (l + r) >> 1;
    if (p <= mid)
      Update(ls, p);
    else
      Update(rs, p);
    PushUp(rt);
  }

  Matrix Query(int rt, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
      return t[rt];
    // printf("%d %d %d %d %d\n", rt, l, r, ql, qr);
    int mid = (l + r) >> 1;
    if (qr <= mid)
      return Query(ls, ql, qr);
    if (ql > mid)
      return Query(rs, ql, qr);
    return Query(ls, ql, qr) * Query(rs, ql, qr);
  }
} st;

// dp_{u, 0} dp_{u, 1}
//

void Dfs3(int u) {
  ldp[u][1] = a[u];
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa[u] || v == son[u])
      continue;
    Dfs3(v);
    ldp[u][0] += std::max(dp[v][0], dp[v][1]);
    ldp[u][1] += dp[v][0];
  }
  dp[u][0] = ldp[u][0], dp[u][1] = ldp[u][1];
  if (son[u]) {
    Dfs3(son[u]);
    dp[u][0] += std::max(dp[son[u]][0], dp[son[u]][1]);
    dp[u][1] += dp[son[u]][0];
  }
}

void Update(int x, int k) {
  mat[x].a[1][0] += k;
  a[x] += k;
  while (x) {
    int _x = x;
    x = tp[x];
    Matrix pre = st.Query(1, 1, n, in[x], ou[x]);
    // printf("pre: "), pre.Print();
    st.Update(1, 1, n, in[_x]);
    Matrix now = st.Query(1, 1, n, in[x], ou[x]);
    // printf("now: "), now.Print();
    x = fa[x];
    mat[x].a[0][0] +=
        std::max(now.a[0][0], now.a[1][0]) - std::max(pre.a[0][0], pre.a[1][0]);
    mat[x].a[0][1] = mat[x].a[0][0];
    mat[x].a[1][0] += now.a[0][0] - pre.a[0][0];
    // printf("mat[%d]: ", x), mat[x].Print();
  }
}

int Query() {
  Matrix res = st.Query(1, 1, n, in[1], ou[1]);
  // res.Print();
  return std::max(res.a[0][0], res.a[1][0]);
}

signed main() {
  freopen("defense.in", "r", stdin);
  freopen("defense.out", "w", stdout);
  char typ[10];
  scanf("%lld%lld%s", &n, &m, typ);
  int sum = 0;
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]), sum += a[i];
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%lld%lld", &u, &v);
    AddEdge(u, v), AddEdge(v, u);
  }
  Dfs1(1, 0), Dfs2(1, 0, 1), Dfs3(1);
  st.Build(1, 1, n);
  while (m--) {
    int u, v, x, y;
    scanf("%lld%lld%lld%lld", &u, &x, &v, &y);
    if (x == 1)
      Update(u, -INF);
    else
      Update(u, INF);
    if (y == 1)
      Update(v, -INF);
    else
      Update(v, INF);
    if ((fa[u] == v || fa[v] == u) && !x && !y) {
      printf("-1\n");
    } else {
      printf("%lld\n", sum - Query() + (x ? 0 : INF) + (y ? 0 : INF));
    }
    if (x == 1)
      Update(u, INF);
    else
      Update(u, -INF);
    if (y == 1)
      Update(v, INF);
    else
      Update(v, -INF);
  }
  return 0;
}
