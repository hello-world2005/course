#include <cstdio>

const int N = 1e5 + 10;

int n, k, q;
struct Edge {
  int v, nxt;

  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt;
int a[N];

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

int ans[N];

void Dfs(int u, int fa) {
  for (int i = head[u]; i; i = e[i].nxt) {}
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  for (int i = 2, u, v; i <=n; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v);
    AddEdge(v, u);
  }
  Dfs(1, 0);
  scanf("%d", &q);
  while (q--) {
    int u;
    scanf("%d", &u);
    printf("%d\n", ans[u]);
  }
  return 0;
}
