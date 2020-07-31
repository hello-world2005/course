#include <algorithm>
#include <cmath>
#include <cstdio>
#include <deque>
#include <vector>

const int N = 1e6 + 10;

int que[N];
int dp[N];
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

int dep[N], cnt[N], s[N];

void Dfs(int u, int fa) {
  dep[u] = dep[fa] + 1;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    Dfs(v, u);
  }
}

double Slope(int x, int y) {
  return 1.0 * (s[x] - s[y]) / (x - y);
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int maxque = 0;
  for (int i = 1; i <= m; ++i)
    scanf("%d", &que[i]), maxque = std::max(maxque, que[i]);
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%d", &u), v = i;
    AddEdge(u, v), AddEdge(v, u);
  }
  Dfs(1, 0);
  int maxdep = 0;
  for (int i = 1; i <= n; ++i)
    ++cnt[dep[i]], maxdep = std::max(maxdep, dep[i]);
  for (int i = maxdep; i >= 0; --i)
    s[i] = s[i + 1] + cnt[i + 1];
  std::vector<int> q;
  q.resize(N);
  int hd = 0, tl = 0;
  for (int i = 1; i <= maxdep; ++i) {
    while (hd < tl && Slope(q[tl - 1], q[tl]) <= Slope(q[tl], i))
      --tl;
    q[++tl] = i;
  }
  for (int i = 1; i <= maxque; ++i) {
    while (hd < tl && i * q[hd] + s[q[hd]] <= i * q[hd + 1] + s[q[hd + 1]])
      ++hd;
    dp[i] = q[hd] + ceil(1.0 * s[q[hd]] / i);
  }
  for (int i = 1; i <= m; ++i)
    printf("%d ", dp[que[i]]);
  printf("\n");
  return 0;
}
