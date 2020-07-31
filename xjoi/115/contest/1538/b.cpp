#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>

#define int long long

const int N = 1e5 + 10;

int n, r;
int fa[N], f[N], sze[N];
int sum[N];
std::vector<int> E[N];

struct Node {
  int u, sze;
  int sum;

  Node() : u(0), sze(0), sum(0) {}
  Node(int u = 0, int sze = 0, int sum = 0) : u(u), sze(sze), sum(sum) {}

  bool operator<(const Node& rhs) const {
    return std::make_pair(sum * rhs.sze, u) >
           std::make_pair(rhs.sum * sze, rhs.u);
  }
};

int Find(int x) {
  if (f[x] == x)
    return x;
  return f[x] = Find(f[x]);
}

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

void Dfs(int u, int fa) {
  ::fa[u] = fa;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    Dfs(v, u);
  }
}

signed main() {
  scanf("%lld%lld", &n, &r);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &sum[i]);
  for (int u, v, i = 1; i < n; ++i) {
    scanf("%lld%lld", &u, &v);
    AddEdge(u, v), AddEdge(v, u);
  }
  Dfs(r, 0);
  for (int i = 1; i <= n; ++i)
    f[i] = i;
  std::set<Node> s;
  for (int i = 1; i <= n; ++i)
    s.insert(Node(i, sze[i] = 1, sum[i]));
  sze[0] = 1;
  int ans = 0;
  while (!s.empty()) {
    Node t = *s.begin();
    s.erase(s.begin());
    int u = t.u, fat = f[Find(u)] = Find(fa[u]);
    ans += sum[u] * sze[fat];
    if (fat > 0)
      s.erase(s.find(Node(fat, sze[fat], sum[fat])));
    sum[fat] += sum[u];
    sze[fat] += sze[u];
    if (fat > 0)
      s.insert(Node(fat, sze[fat], sum[fat]));
  }
  printf("%lld\n", ans);
  return 0;
}
