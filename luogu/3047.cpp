#include <cstdio>

const int N = 1e5 + 10;
const int K = 30;

int n, k;
struct Edge {
  int v, nxt;

  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v) {
  e[++edge_cnt] =Edge(v, head[u]);
  head[u] = edge_cnt;
}

int val[N];
int f[N][K];

void Dfs1(int u, int fa) {
  f[u][0] = val[u];
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    Dfs1(v, u);
    for (int j = 1; j <= k; ++j)
      f[u][j] += f[v][j - 1];
  }
}

void Dfs2(int u, int fa) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    for (int j = k; j >= 2; --j)
      f[v][j] -= f[v][j - 2];
    for (int j = 1; j <= k; ++j)
      f[v][j] += f[u][j - 1];
    Dfs2(v, u);
  }
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v), AddEdge(v, u);
  }
  for (int i = 1; i <= n; ++i)
    scanf("%d", &val[i]);
  Dfs1(1, 0), Dfs2(1, 0);
  for (int i = 1; i <= n; ++i) {
    int sum = 0;
    for (int j = 0; j <= k; ++j)
      sum += f[i][j];
    printf("%d\n", sum);
  }
  return 0;
}
