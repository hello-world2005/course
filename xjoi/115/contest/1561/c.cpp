#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>

const int N = 10;
const int MOD = 998244353;

int n;
// struct Edge {
//   int v, nxt;

//   Edge() : v(0), nxt(0) {}
//   Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
// } e[N << 1];
// int head[N], edge_cnt;

// void AddEdge(int u, int v) {
//   e[++edge_cnt] = Edge(v, head[u]);
//   head[u] = edge_cnt;
// }
std::vector<int> e[N];

void AddEdge(int u, int v) { e[u].push_back(v); }

std::vector<std::pair<int, int> > edge;

int sze[N];

void Dfs(int u, int fa) {
  sze[u] = 1;
  for (int v : e[u]) {
    if (v == fa)
      continue;
    Dfs(v, u);
    sze[u] += sze[v];
  }
}

int Solve() {
  memset(sze, 0, sizeof(sze));
  int res = 0;
  for (int i = 0; i < n; ++i)
    if (!sze[i])
      Dfs(i, 0), res += sze[i] * sze[i];
  return res;
}

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % MOD)
    if (b & 1)
      res = 1ll * res * a % MOD;
  return res;
}

int Inv(int a) { return FastPow(a, MOD - 2); }

int fac[N], ans[N];
bool vis[N];

std::vector<int> de;
std::set<std::vector<int> > qaq;

void QwQ(int dep, int cho) {
  if (dep >= n - 1) {
    if (qaq.find(de) == qaq.end()) {
      (ans[cho] += Solve()) %= MOD, (++fac[cho]) %= MOD, qaq.insert(de);
      // printf("> %d %d: ", dep, cho);
      // for (auto i : de)
      //   printf("%d ", i);
      // for (int i = 0; i < n; ++i)
      //   for (int j : e[i])
      //     printf("(%d, %d)  ", i, j);
      // printf("\n");
    }
    return;
  }
  QwQ(dep + 1, cho);
  for (int i = dep; i < n - 1; ++i)
    AddEdge(edge[i].first, edge[i].second), AddEdge(edge[i].second, edge[i].first), de.push_back(i),
    QwQ(i + 1, cho + 1),
    e[edge[i].first].pop_back(), e[edge[i].second].pop_back(), de.pop_back();
}

int main() {
  scanf("%d", &n);
  edge.resize(n - 1);
  for (int i = 0; i < n - 1; ++i)
    scanf("%d%d", &edge[i].first, &edge[i].second), --edge[i].first, --edge[i].second;
  QwQ(0, 0);
  for (int i = n - 1; i >= 0; --i)
    printf("%d ", (int)(1ll * ans[i] * Inv(fac[i]) % MOD));
  printf("\n");
  // for (int i = 0; i < n; ++i)
  //   printf("%d %d\n", ans[i], fac[i]);
  return 0;
}
