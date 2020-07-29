#include <cstdio>

typedef long long ll;

const int N = 1e5 + 10;

int n;
struct Edge {
  int v, w, nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int dep[N], sze[N];

void Dfs1(int u, int fa) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v, w = e[i].w;
    if (v == fa)
      continue;
    dep[v] = dep[u] + w;
    Dfs1(v, u);
    sze[u] += sze[v];
  }
}

ll ans[N];
int tot;

void Dfs2(int u, int fa, ll sum) {
  ans[u] = sum;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v, w = e[i].w;
    if (v == fa)
      continue;
    Dfs2(v, u, sum - 1ll * w * sze[v] + 1ll * w * (tot - sze[v]));
  }
}

int _sze[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &sze[i]), _sze[i] = sze[i], tot += sze[i];
  for (int i = 2, u, v, w; i <= n; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    AddEdge(u, v, w), AddEdge(v, u, w);
  }
  Dfs1(1, 0);
  ll s = 0;
  for (int i = 1; i <= n; ++i)
    s += 1ll * _sze[i] * dep[i];
  Dfs2(1, 0, s);
  ll minn = 1;
  for (int i = 1; i <= n; ++i)
    if (ans[i] < ans[minn])
      minn = i;
  // for (int i = 1; i <= n; ++i)
  //   printf("%lld ", ans[i]);
  // printf("\n");
  printf("%lld\n", ans[minn]);
  return 0;
}
