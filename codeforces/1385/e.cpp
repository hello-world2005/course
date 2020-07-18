#include <algorithm>
#include <cstdio>
#include <queue>

const int N = 1e6 + 10;

int n, m;
int deg[N], vis[N];
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
int x[N], y[N], opt[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    std::queue<int> q;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
      head[i] = 0, vis[i] = 0, deg[i] = 0;
    edge_cnt = 0;
    for (int i = 1; i <= m; ++i) {
      scanf("%d%d%d", &opt[i], &x[i], &y[i]);
      if (opt[i])
        AddEdge(x[i], y[i]), ++deg[y[i]];
    }
    int idx = 0;
    for (int i = 1; i <= n; ++i)
      if (!deg[i]) {
        vis[i] = ++idx;
        q.push(i);
      }
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (!(--deg[v])) {
          vis[v] = ++idx;
          q.push(v);
        }
      }
    }
    for (int i = 1; i <= n; ++i)
      if (vis[i] == 0) {
        printf("NO\n");
        goto ed;
      }
    printf("YES\n");
    for (int i = 1; i <= m; ++i) {
      if (opt[i])
        printf("%d %d\n", x[i], y[i]);
      else if (vis[x[i]] < vis[y[i]])
        printf("%d %d\n", x[i], y[i]);
      else
        printf("%d %d\n", y[i], x[i]);
    }
    ed:;
  }
  return 0;
}