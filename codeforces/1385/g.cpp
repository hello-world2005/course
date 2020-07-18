#include <algorithm>
#include <cstdio>
#include <vector>

const int N = 2e5 + 10;

int a[N], b[N];
int deg[N];
int fa[N], siz[N];
std::vector<int> id[N], g[N], w[N], to[2], res;
int ch[2], vis[N];

void AddEdge(int u, int v, int t) {
  g[u].push_back(v);
  w[u].push_back(t);
  return;
}

void Dfs(int u, int col) {
  vis[u] = 1;
  ++ch[col];
  to[col].push_back(u);
  for (int i = 0; i < (int)g[u].size(); ++i) {
    int v = g[u][i];
    int t = w[u][i];
    if (vis[v])
      continue;
    Dfs(v, col ^ t);
  }
  return;
}

void FYYAKIOI() {
  ch[1] = ch[0] = 0;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    res.clear();
    FYYAKIOI();
    for (int i = 1; i <= n; ++i)
      id[i].clear(), g[i].clear(), w[i].clear(), deg[i] = 0, vis[i] = 0;
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &b[i]);
    for (int i = 1; i <= n; ++i)
      ++deg[a[i]], ++deg[b[i]];
    int flag = false;
    for (int i = 1; i <= n; ++i)
      if (deg[i] != 2)
        flag = true;
    if (flag) {
      printf("-1\n");
      continue;
    }
    for (int i = 1; i <= n; ++i) {
      id[a[i]].push_back(i);
      id[b[i]].push_back(i + n);
    }
    for (int i = 1; i <= n; ++i) {
      int x = id[i][0], y = id[i][1], op = 0;
      if (x > n)
        x -= n, op ^= 1;
      if (y > n)
        y -= n, op ^= 1;
      AddEdge(x, y, op ^ 1);
      AddEdge(y, x, op ^ 1);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
      if (!vis[i]) {
        ch[0] = ch[1] = 0;
        to[0].clear(), to[1].clear();
        Dfs(i, 0);
        ans += std::min(ch[0], ch[1]);
        if (ch[0] > ch[1])
          std::swap(to[0], to[1]);
        for (int j = 0; j < (int)to[0].size(); ++j)
          res.push_back(to[0][j]);
      }
    printf("%d\n", ans);
    for (int i = 0; i < (int)res.size(); ++i)
      printf("%d ", res[i]);
    printf("\n");
  }
  return 0;
}