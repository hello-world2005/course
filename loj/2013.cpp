#include <algorithm>
#include <cstdio>

typedef long long ll;

const int N = 2e4 + 10;
const int K = 70;

int n, q;
ll val[N];
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

ll d[N][20][K];

bool Insert(ll* d, ll k) {
  for (int i = 62; i >= 0; --i)
    if (k >> i & 1) {
      if (!d[i]) {
        d[i] = k;
        return true;
      } else {
        k ^= d[i];
      }
    }
  return false;
}

ll Query(ll* d, ll k = 0) {
  ll res = k;
  for (int i = 62; i >= 0; --i)
    res = std::max(res, res ^ d[i]);
  return res;
}

int dep[N], f[N][20];

void Dfs(int u, int fa) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    dep[v] = dep[u] + 1;
    f[v][0] = u;
    Dfs(v, u);
  }
}

void Merge(ll* d1, ll* d2) {
  for (int i = 62; i >= 0; --i)
    if (d2[i])
      Insert(d1, d2[i]);
}

void InitLca() {
  dep[1] = 1;
  Dfs(1, 0);
  for (int j = 1; j < 20; ++j)
    for (int i = 1; i <= n; ++i) {
      f[i][j] = f[f[i][j - 1]][j - 1];
      Merge(d[i][j], d[i][j - 1]);
      Merge(d[i][j], d[f[i][j - 1]][j - 1]);
    }
}

int Lca(int u, int v, ll* ans) {
  if (dep[u] < dep[v])
    std::swap(u, v);
  for (int i = 19; i >= 0; --i)
    if (dep[f[u][i]] >= dep[v]) {
      Merge(ans, d[u][i]);
      u = f[u][i];
    }
  if (u == v) {
    Merge(ans, d[u][0]);
    return u;
  }
  for (int i = 19; i >= 0; --i)
    if (f[u][i] != f[v][i]) {
      Merge(ans, d[u][i]);
      Merge(ans, d[v][i]);
      u = f[u][i], v = f[v][i];
    }
  Merge(ans, d[u][0]);
  Merge(ans, d[v][0]);
  Merge(ans, d[f[u][0]][0]);
  return f[u][0];
}

ll Solve(int u, int v) {
  ll ans[K] = {0};
  int lca = Lca(u, v, ans);
  // printf("%d %d %d\n", u, v, lca);
  return Query(ans);
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &val[i]);
    Insert(d[i][0], val[i]);
  }
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v);
    AddEdge(v, u);
  }
  InitLca();
  while (q--) {
    int u, v;
    scanf("%d%d", &u, &v);
    printf("%lld\n", Solve(u, v));
  }
  return 0;
}
