#include <algorithm>
#include <cstdio>
#include <vector>

#define int long long

const int N = 2e5 + 10;

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

int a[N], b[N];
int deg[N];
int ans;
std::vector<int> qwq, qaq;
bool vis[N];

void Dfs(int u, int fa) {
  vis[u] = true;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (vis[v])
      continue;
    Dfs(v, u);
    if (a[v] > 0)
      a[u] += a[v];
  }
  ans += a[u];
  if (a[u] > 0)
    qwq.push_back(u);
  else
    qaq.push_back(u);
}

signed main() {
  int n;
  scanf("%lld", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &b[i]);
    if (b[i] != -1)
      AddEdge(b[i], i), AddEdge(i, b[i]);
  }
  for (int i = 1; i <= n; ++i)
    if (b[i] == -1)
      Dfs(i, 0);
  // for (int i = 1; i <= n; ++i)
  //   printf("%lld\n", a[i]);
  printf("%lld\n", ans);
  std::reverse(qaq.begin(), qaq.end());
  for (auto i : qwq)
    printf("%lld ", i);
  for (auto i : qaq)
    printf("%lld ", i);
  printf("\n");
  return 0;
}

// 10
// -10 -1 2 2 5 -2 -3 -4 2 -6
// -1 -1 2 2 -1 5 5 7 7 9

// -9
// 3 5 6 1 9 4 10 7 8 2
