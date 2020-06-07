#include <algorithm>
#include <cstdio>
#include <vector>

const int N = 1e4 + 10;

int n, m;
struct Edge {
  int v, nxt;

  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} e[N];
int head[N], edge_cnt;

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
}

int low[N], dfn[N], ti_stamp;
int s[N], tp, vis[N];
int sum[N], color, bcc[N];

void Tarjan(int u) {
  low[u] = dfn[u] = ++ti_stamp;
  s[++tp] = u;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (!dfn[v]) {
      Tarjan(v);
      low[u] = std::min(low[u], low[v]);
    } else if (vis[v]) {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    int cnt = 0;
    ++color;
    do {
      vis[s[tp]] = false;
      bcc[s[tp--]] = color;
    } while (s[tp + 1] != u);
  }
}

std::vector<int> ed[N];
int dp[N];

void Dfs(int u, int fa) {
  dp[u] = s[u];
  for (auto v : ed) {}
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v);
  }
  for (int i = 1; i <= n; ++i)
    if (!dfn[i])
      Tarjan(i);
  for (int u = 1; u <= n; ++u)
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v;
      if (bcc[u] != bcc[v])
        ed[bcc[u]].push_back(bcc[v]);
    }
  Dfs(1, 0);
  printf("%d\n", dp[bcc[1]]);
}

// 大概思路：缩点后 DP
// 不想写了
