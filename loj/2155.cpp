#include <algorithm>
#include <cstdio>

const int N = 5010;

struct Edge {
  int v, nxt;

  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} e[N];
int head[N << 1], edge_cnt;

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

int dfn[N], low[N], idx;
int col[N], color;
int stk[N], top;
bool instk[N];

void Tarjan(int u) {
  dfn[u] = low[u] = ++idx;
  stk[++top] = u, instk[u] = true;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (!dfn[v]) {
      Tarjan(v);
      low[u] = std::min(low[u], low[v]);
    } else if (instk[v]) {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
  if (dfn[u] == low[u]) {
    ++color;
    do {
      int t = stk[top--];
      instk[t] = false;
      col[t] = color;
    } while (stk[top] != u);
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1, k; i <= n; ++i) {
    scanf("%d", &k);
    for (int i = 1, v; i <= k; ++i) {}
  }
}
