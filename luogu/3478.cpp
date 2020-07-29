#include <cstdio>

#define int long long

const int N = 1e6 + 10;

int n;
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

int dep[N], sze[N];

void Dfs1(int u, int fa) {
  sze[u] = 1;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    dep[v] = dep[u] + 1;
    Dfs1(v, u);
    sze[u] += sze[v];
  }
}

int ans[N];

void Dfs2(int u, int fa, int sum) {
  ans[u] = sum;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    Dfs2(v, u, sum - 2 * sze[v] + n);
  }
}

signed main() {
  scanf("%lld", &n);
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%lld%lld", &u, &v);
    AddEdge(u, v), AddEdge(v, u);
  }
  Dfs1(1, 0);
  int s = 0;
  for (int i = 1; i <= n; ++i)
    s += dep[i];
  Dfs2(1, 0, s);
  int maxn = 0;
  for (int i = 1; i <= n; ++i)
    if (ans[i] > ans[maxn])
      maxn = i;
  // for (int i = 1; i <= n; ++i)
  //   printf("%lld ", ans[i]);
  // printf("\n");
  printf("%lld\n", maxn);
  return 0;
}
