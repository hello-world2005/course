#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

const int N = 5e3 + 10;
const int M = 1e5 + 10;

int n, m;
struct Edge {
  int v, nxt;

  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} e[M << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

// 二分图
int col[N];

void Check(int u) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (!col[v]) {
      col[v] = (col[u] == 1 ? 2 : 1);
      Check(v);
    } else if (col[v] == col[u]) {
      // printf("%d %d %d %d ", u, v, col[u], col[v]);
      printf("NO\n");
      exit(0);
    }
  }
}

// DP
bool vis[N];
std::vector<int> s1[N], s2[N];

void Dfs(int u, int cnt) {
  if (col[u] == 1)
    s1[cnt].push_back(u);
  else
    s2[cnt].push_back(u);
  vis[u] = true;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (!vis[v])
      Dfs(v, cnt);
  }
}

int n1, n2, n3;
int dp[N][N];
int tag[N];

int main() {
  scanf("%d%d", &n, &m);
  scanf("%d%d%d", &n1, &n2, &n3);
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v);
    AddEdge(v, u);
  }
  for (int i = 1; i <= n; ++i)
    if (!col[i])
      col[i] = 1, Check(i);
  int cnt = 0;
  for (int i = 1; i <= n; ++i)
    if (!vis[i])
      ++cnt, Dfs(i, cnt);
  dp[0][0] = 1;
  for (int i = 1; i <= cnt; ++i)
    for (int j = 0; j <= n; ++j) {
      if (s1[i].size() <= j)
        dp[i][j] |= dp[i - 1][j - s1[i].size()];
      if (s2[i].size() <= j)
        dp[i][j] |= dp[i - 1][j - s2[i].size()];
    }
  if (!dp[cnt][n2]) {
    printf("NO\n");
    return 0;
  }
  printf("YES\n");
  int now = n2;
  for (int i = cnt; i >= 1; --i)
    if (dp[i - 1][now - s1[i].size()])
      tag[i] = 1, now -= s1[i].size();
    else if (dp[i - 1][now - s2[i].size()])
      tag[i] = 2, now -= s2[i].size();
  memset(col, 0, sizeof(col));
  for (int i = 1; i <= cnt; ++i)
    if (tag[i] == 1)
      for (int j : s1[i])
        col[j] = 2;
    else
      for (int j : s2[i])
        col[j] = 2;
  int s1 = 0;
  for (int i = 1; i <= n; ++i)
    if (!col[i]) {
      if (s1 < n1)
        col[i] = 1, ++s1;
      else
        col[i] = 3;
    }
  for (int i = 1; i <= n; ++i)
    printf("%d", col[i]);
  printf("\n");
  return 0;
}
