#include <algorithm>
#include <cmath>
#include <cstdio>
#include <deque>

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

int Slope(int x, int y) {
  return (s[x] - s[y]) / (x - y);
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
  std::deque<int> q;
  // q.push_back(0);
  for (int i = 1; i <= maxdep; ++i) {
    while (q.size() >= 2 &&
           Slope(q[q.size() - 2], q[q.size() - 1] <= Slope(q[q.size() - 1], i)))
      q.pop_back();
    q.push_back(i);
  }
  for (int i = 1; i <= maxque; ++i) {
    while (q.size() >= 2 && i * q[0] + s[q[0]] <= i * q[1] + s[q[1]])
      q.pop_front();
    dp[i] = q[0] + ceil(1.0 * s[q[0]] / i);
  }
  for (int i = 1; i <= m; ++i)
    printf("%d ", dp[que[i]]);
  printf("\n");
  return 0;
}
