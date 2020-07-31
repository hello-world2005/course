#include <cstdio>

const int N = 4e5 + 10;

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

int sze[N], dp[N][2], son[N];

void Dfs1(int u, int fa) {
  sze[u] = 1;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v, t;
    if (v == fa)
      continue;
    Dfs1(v, u);
    sze[u] += v;
    if (sze[son[u]] < sze[v])
      son[u] = v;
    if (sze[v] <= n / 2)
      t = sze[v];
    else
      t = dp[v][0];
    if (dp[u][0] < t)
      dp[u][1] = dp[u][0], dp[u][0] = t;
    else if (dp[u][1] < t)
      dp[u][1] = t;
  }
}

int ans[N];

void Dfs2(int u, int fa) {
  ans[u] = true;
  if (sze[son[u]] > n / 2)
    ans[u] = (sze[son[u]] - dp[son[u]][0] <= n / 2);
  else if (n - sze[u] > n / 2)
    ans[u] = ;
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v), AddEdge(v, u);
  }
  Dfs1(1, 0), Dfs2(1, 0);
  for (int i = 1; i <= n; ++i)
    printf("%d ", ans[i]);
  printf("\n");
  return 0;
}
