#include <algorithm>
#include <cstdio>

const int N = 1e6 + 10;

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

int p[N];
int in[N], ou[N], idx;
int dis[N], fa[N];

void Dfs(int u, int fa) {
  in[u] = ++idx, ::fa[u] = fa;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v, w = e[i].w;
    if (v == fa)
      continue;
    dis[v] = dis[u] + w;
    Dfs(v, u);
  }
  ou[u] = idx;
}

bool vis[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 2, u, v, w; i <= n; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    AddEdge(u, v, w), AddEdge(v, u, w);
  }
  for (int i = 1; i <= n; ++i)
    scanf("%d", &p[i]);
  Dfs(p[1], 0);
  printf("0\n");
  int ans = 0;
  for (int i = 2; i <= n; ++i) {
    while (p[i] != p[1] && !vis[p[i]])
      ans += dis[p[i]] - dis[fa[p[i]]], vis[p[i]] = true, p[i] = fa[p[i]];
    printf("%d\n", ans);
  }
  return 0;
}
