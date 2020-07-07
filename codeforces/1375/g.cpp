#include <algorithm>
#include <cstdio>

const int N = 2e5 + 10;

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

int col[N];
int cnt[10];

void Dfs(int u, int fa) {
  col[u] = (col[fa] & 1) ? 2 : 1;
  ++cnt[col[u]];
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    Dfs(v, u);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v);
    AddEdge(v, u);
  }
  Dfs(1, 0);
  printf("%d\n", std::min(cnt[1], cnt[2]) - 1);
  return 0;
}
