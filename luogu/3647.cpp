#include <algorithm>
#include <cstdio>
#include <vector>

const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int n;
struct Edge {
  int v, w, nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

std::vector<int> f[N][2], maxn[N];
int dp[N][2];

void Dfs1(int u, int fa) {
  dp[u][0] = 0, dp[u][1] = -INF;
  int maxn1 = -INF, maxn2 = -INF;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v, w = e[i].w;
    if (v == fa)
      continue;
    Dfs1(v, u);
    dp[u][0] += std::max(dp[v][0], dp[v][1] + w);
    if (dp[v][0] + w - std::max(dp[v][0], dp[v][1] + w) > maxn1)
      maxn2 = maxn1, maxn1 = dp[v][0] + w - std::max(dp[v][0], dp[v][1] + w);
    else if (dp[v][0] + w - std::max(dp[v][0], dp[v][1] + w) > maxn2)
      maxn2 = dp[v][0] + w - std::max(dp[v][0], dp[v][1] + w);
  }
  dp[u][1] = dp[u][0] + maxn1;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v, w = e[i].w;
    if (v == fa)
      continue;
    f[u][0].push_back(dp[u][0] - std::max(dp[v][0], dp[v][1] + w));
    if (dp[v][0] + w - std::max(dp[v][0], dp[v][1] + w) == maxn1) {
      f[u][1].push_back(f[u][0].back() + maxn2);
      maxn[u].push_back(maxn2);
    } else {
      f[u][1].push_back(f[u][0].back() + maxn1);
      maxn[u].push_back(maxn1);
    }
  }
}

int ans;

void Dfs2(int u, int fa, int l) {
  for (int i = head[u], cnt = 0; i; i = e[i].nxt) {
    int v = e[i].v, w = e[i].w;
    if (v == fa)
      continue;
    dp[u][0] = f[u][0][cnt], dp[u][1] = f[u][1][cnt];
    if (fa) {
      dp[u][0] += std::max(dp[fa][0], dp[fa][1] + l);
      dp[u][1] = dp[u][0] +
                 std::max(maxn[u][cnt],
                          dp[fa][0] + l - std::max(dp[fa][0], dp[fa][1] + l));
    }
    ans = std::max(ans, dp[v][0] + std::max(dp[u][0], dp[u][1] + w));
    Dfs2(v, u, w);
    ++cnt;
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v, w; i <= n; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    AddEdge(u, v, w), AddEdge(v, u, w);
  }
  Dfs1(1, 0);
  // for (int i =1; i <= n; ++i)
  //   printf("> %d %d\n", dp[i][0], dp[i][1]);
  Dfs2(1, 0, 0);
  printf("%d\n", ans);
  return 0;
}
