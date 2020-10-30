#include <cstdio>

const int N = 1e5 + 10;
const int MOD = 1e9 + 7;

struct Edge {
  int v, nxt;

  Edge()
      : v(0), nxt(0) {}
  Edge(int _v, int _nxt)
      : v(_v), nxt(_nxt) {}
} e[N];
int head[N], edge_cnt;

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

int a[N], dp[N][2];

void Dfs(int u) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    Dfs(v);
    dp[u][1] = (1ll * dp[u][1] * (dp[v][0] + dp[v][1]) % MOD + 1ll * dp[u][0] * dp[v][1] % MOD) % MOD;
    dp[u][0] = 1ll * dp[u][0] * (dp[v][0] + dp[v][1]) % MOD;
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 2, p; i <= n; ++i) {
    scanf("%d", &p), ++p;
    AddEdge(p, i);
  }
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), dp[i][a[i]] = 1;
  Dfs(1);
  printf("%d\n", dp[1][1]);
  return 0;
}
