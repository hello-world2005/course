#include <algorithm>
#include <cstdio>

const int N = 1e5 + 10;

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

int sze[N], f[N], center;

void GetCenter(int u, int fa) {
  sze[u] = 1, f[u] = 0;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    GetCenter(v, u);
    sze[u] += sze[v];
    f[u] = std::max(f[u], sze[v]);
  }
  f[u] = std::max(f[u], n - sze[u]);
  if (f[u] < f[center])
    center = u;
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v);
    AddEdge(v, u);
  }
  f[center] = n;
  GetCenter(1, 0);
  printf("%d\n", f[center]);
  return 0;
}
