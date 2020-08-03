#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int N = 1e5 + 10;

int n, m;
struct Edge {
  int v, nxt;

  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt = 1;

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

int dfn[N], idx, fa[N];
int dp[N][3][2][3], g[8][3][2][3];
int col[N], color, in_r[N << 1];

void Paint(int u, int v) {
  // printf("%lld %lld\n", u, v);
  if (u == v)
    return;
  int i = fa[u];
  col[u] = color;
  if (in_r[i])
    printf("-1\n"), exit(0);
  in_r[i] = in_r[i ^ 1] = 1;
  Paint(e[i ^ 1].v, v);
}

void Dfs(int u, int fa) {
  dfn[u] = ++idx;
  bool flag = false;
  for (int i = head[u]; i; i = e[i].nxt)
    if (e[i].v != fa && dfn[e[i].v])
      flag = true;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    if (!dfn[v]) {
      ::fa[v] = i;
      Dfs(v, u);
      memset(g, 0, sizeof(g));
      for (int mask = 0; mask < (1 << 3); ++mask)
        for (int j = 0; j <= 2; ++j)
          for (int x = 0; x <= 1; ++x)
            for (int y = 0; y <= 2; ++y)
              ;
    } else if (dfn[v] < dfn[u]) {
      ++color;
      Paint(u, v);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v), AddEdge(v, u);
  }
  for (int i = 1; i <= n; ++i)
    if (!dfn[i]) {
      Dfs(1, 0);
    }
}
