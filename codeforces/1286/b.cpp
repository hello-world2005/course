#include <cstdio>
#include <cstdlib>
#include <vector>

const int N = 2010;

struct Edge {
  int v, nxt;

  Edge()
      : v(0), nxt(0) {}
  Edge(int _v, int _nxt)
      : v(_v), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

int a[N];

std::vector<int> res[N];

void Dfs(int u, int fa) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    Dfs(v, u);
    for (int j : res[v]) {
      if (res[u].size() == a[u])
        res[u].push_back(u);
      res[u].push_back(j);
    }
  }
  if (res[u].size() == a[u])
    res[u].push_back(u);
  if (res[u].size() < a[u])
    printf("NO\n"), exit(0);
}

int ans[N];

int main() {
  int n, rt;
  scanf("%d", &n);
  for (int i = 1, fa; i <= n; ++i) {
    scanf("%d%d", &fa, &a[i]);
    if (fa)
      AddEdge(fa, i), AddEdge(i, fa);
    else
      rt = i;
  }
  Dfs(rt, 0);
  printf("YES\n");
  for (int i = 0; i < res[rt].size(); ++i)
    ans[res[rt][i]] = i + 1;
  for (int i = 1; i <= n; ++i)
    printf("%d ", ans[i]);
  printf("\n");
  return 0;
}
