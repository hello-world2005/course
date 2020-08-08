#include <cstdio>

const int N = 5e5 + 10;

struct Edge {
  int v, w, nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt;
int p[N];

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

double q[N], dp[N], ans[N];

void Dfs1(int u, int fa) {
  dp[u] = 1 - p[u] / 100.0;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    double w = e[i].w / 100.0;
    if (v == fa)
      continue;
    Dfs1(v, u);
    dp[u] *= (1 - w + w * dp[v]);
  }
}

void Dfs2(int u, int fa) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    double w = e[i].w / 100.0;
    if(v == fa)
      continue;
    ans[v] = dp[v] * (1 - w + w * ans[u] / (1 - w + w * dp[v]));
    Dfs2(v, u);
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 2, u, v, w; i <= n; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    AddEdge(u, v, w), AddEdge(v, u, w);
  }
  for (int i = 1; i <= n; ++i)
    scanf("%d", &p[i]);
  Dfs1(1, 0), ans[1] = dp[1], Dfs2(1, 0);
  // for (int i = 1; i <= n; ++i)
  //   printf("%lf\n", dp[i]);
  double ans = 0;
  for (int i = 1; i <= n; ++i)
    ans += 1 - ::ans[i];
  printf("%.6lf\n", ans);
  return 0;
}
