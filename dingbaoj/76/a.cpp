#include <algorithm>
#include <cstdio>
#include <vector>

const int N = 1e5 + 10;

int n, k, q;
struct Edge {
  int v, nxt;

  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt;
int a[N];
std::vector<int> b(N);

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

int ans[N];

int sze[N], s[N];  // size son

void GetSze(int u, int fa) {
  sze[u] = 1;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    GetSze(v, u);
    sze[u] += sze[v];
    if (sze[s[u]] < sze[v])
      s[u] = v;
  }
}

int cnt[N], sum;
bool vis[N];

void Calc(int u, int fa, int d) {
  if (cnt[a[u]] == k)
    --sum;
  cnt[a[u]] += d;
  if (cnt[a[u]] == k)
    ++sum;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa || vis[v])
      continue;
    Calc(v, u, d);
  }
}

void Dfs(int u, int fa, bool flag) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa || v == s[u])
      continue;
    Dfs(v, u, 0);
  }
  if (s[u]) {
    Dfs(s[u], u, true);
    vis[s[u]] = 1;
  }
  Calc(u, fa, 1);
  ans[u] = sum;
  if (s[u])
    vis[s[u]] = false;
  if (!flag) {
    Calc(u, fa, -1);
    sum = 0;
  }
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), b[i] = a[i];
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  for (int i = 1; i <= n; ++i)
    a[i] = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin();
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v);
    AddEdge(v, u);
  }
  GetSze(1, 0);
  // for (int i = 1; i <= n; ++i)
  //   printf("%d %d\n", sze[i], s[i]);
  Dfs(1, 0, 0);
  scanf("%d", &q);
  while (q--) {
    int u;
    scanf("%d", &u);
    printf("%d\n", ans[u]);
  }
  return 0;
}
