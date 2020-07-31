#include <cstdio>

const int N = 1e5 + 10;

int n, m;
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

int p[N], h[N];
int qwq[N], qaq[N];
bool flag;

void Dfs(int u, int fa) {
  int sum = 0;
  qaq[u] = p[u];
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    Dfs(v, u);
    sum += qwq[v];
    qaq[u] += qaq[v];
  }
  if ((qaq[u] + h[u]) % 2 != 0)
    flag = false;
  qwq[u] = (qaq[u] + h[u]) / 2;
  if (qwq[u] < 0 || qwq[u] > qaq[u])
    flag = false;
  if (qwq[u] < sum)
    flag = false;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &p[i]);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &h[i]);
    for (int i = 2, u, v; i <= n; ++i) {
      scanf("%d%d", &u, &v);
      AddEdge(u, v), AddEdge(v, u);
    }
    flag = true;
    Dfs(1, 0);
    printf("%s\n", flag ? "YES" : "No");
    for (int i = 1; i <= edge_cnt; ++i)
      e[i] = Edge();
    for (int i = 1; i <= n; ++i)
      head[i] = qwq[i] = qaq[i] = 0;
    edge_cnt = 0;
  }
  return 0;
}
