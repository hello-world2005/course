#include <algorithm>
#include <cstdio>

const int N = 1e4 + 10;
const int M = 5e4 + 10;

struct Edge {
  int v, nxt;

  Edge()
      : v(0), nxt(0) {}
  Edge(int _v, int _nxt)
      : v(_v), nxt(_nxt) {}
} e[M];
int head[N], edge_cnt;

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

int dfn[N], low[N], idx;
int sta[N], tp;
bool in_sta[N];
int scc[N], col, sze[N];

void Tarjan(int u) {
  dfn[u] = low[u] = ++idx;
  sta[++tp] = u, in_sta[u] = true;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (!dfn[v]) {
      Tarjan(v);
      low[u] = std::min(low[u], low[v]);
    } else if (in_sta[v]) {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    ++col;
    while (sta[tp] != u) {
      scc[sta[tp]] = col;
      in_sta[sta[tp--]] = false;
      ++sze[col];
    }
    scc[sta[tp]] = col;
    in_sta[sta[tp--]] = false;
    ++sze[col];
  }
}

int deg[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v);
  }
  for (int i = 1; i <= n; ++i)
    if (!dfn[i])
      Tarjan(i);
  for (int u = 1; u <= n; ++u)
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v;
      if (scc[u] != scc[v])
        ++deg[scc[u]];
    }
  int ans = 0;
  for (int i = 1; i <= col; ++i)
    if (!deg[i]) {
      if (ans)
        return printf("0\n"), 0;
      ans = i;
    }
  printf("%d\n", sze[ans]);
  return 0;
}
