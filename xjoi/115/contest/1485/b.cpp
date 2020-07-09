#include <algorithm>
#include <cstdio>

const int N = 1e5 + 10;
const int M = 2e5 + 10;

int n, m;
struct Edge {
  int v, nxt;

  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} e[M << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

int ans;
int dfn[N], low[N], idx;
int is[N];

void Tarjan(int u, int fa) {
  dfn[u] = low[u] = ++idx;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (!dfn[v]) {
      Tarjan(v, u);
      low[u] = std::min(low[u], low[v]);
      if (low[v] > dfn[u]) {
        is[v] = true;
        ++ans;
      }
    } else if (dfn[u] > dfn[v] && v != fa) {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v);
    AddEdge(v, u);
  }
  for (int u = 1; u <= n; ++u)
    if (!dfn[u])
      Tarjan(u, 0);
  printf("%d\n", ans);
  return 0;
}
