#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e5 + 10;
const int M = 2e5 + 10;
const int K = 60;

struct Edge {
  int v, w, nxt;

  Edge()
      : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt)
      : v(_v), w(_w), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int n, m, k, p;

namespace Subtask1 {
// k == 0
int dis[N], cnt[N];
bool vis[N];

void Dijkstra(int s) {
  std::priority_queue<std::pair<int, int> > q;
  memset(dis, 0x3f, sizeof(dis));
  memset(cnt, 0, sizeof(cnt));
  memset(vis, false, sizeof(vis));
  q.push(std::make_pair(0, s));
  dis[s] = 0, cnt[s] = 1;
  while (!q.empty()) {
    int u = q.top().second;
    q.pop();
    if (vis[u])
      continue;
    vis[u] = true;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].w;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        cnt[v] = cnt[u];
        q.push(std::make_pair(-dis[v], v));
      } else if (dis[v] == dis[u] + w) {
        cnt[v] = (cnt[v] + cnt[u]) % p;
        q.push(std::make_pair(-dis[v], v));
      }
    }
  }
}

void Main() {
  Dijkstra(1);
  printf("%d\n", cnt[n]);
  // for (int i = 1; i <= n; ++i)
  //   printf("%d ", dis[i]);
}
}  // namespace Subtask1

namespace Subtask2 {
// none 0 edge
struct Edge {
  int v, w;

  Edge()
      : v(0), w(0) {}
  Edge(int _v, int _w)
      : v(_v), w(_w) {}
};
std::vector<Edge> e1[N], e2[N];

int dis[N], cnt[N];
bool vis[N];

void Dijkstra(int s) {
  std::priority_queue<std::pair<int, int> > q;
  memset(dis, 0x3f, sizeof(dis));
  memset(cnt, 0, sizeof(cnt));
  memset(vis, false, sizeof(vis));
  q.push(std::make_pair(0, s));
  dis[s] = 0, cnt[s] = 1;
  while (!q.empty()) {
    int u = q.top().second;
    q.pop();
    if (vis[u])
      continue;
    vis[u] = true;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].w;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        cnt[v] = cnt[u];
        q.push(std::make_pair(-dis[v], v));
      } else if (dis[v] == dis[u] + w) {
        cnt[v] = (cnt[v] + cnt[u]) % p;
        q.push(std::make_pair(-dis[v], v));
      }
    }
  }
}

int dp[N][K];

int Solve(int s, int k) {
  memset(dp, 0, sizeof(dp));
  std::queue<int> q;
  q.push(s);
  for (int i = 1; i <= n; ++i)
    dp[i][0] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].w;
      for (int j = 0; j + dis[u] + w <= k + dis[v]; ++j)
        dp[v][j + w] = (dp[v][j + w] + dp[u][j]) % p;
      q.push(v);
    }
  }
  return dp[1][k];
}

void Main() {
  for (int u = 1; u <= n; ++u)
    for (int i = head[u]; i; i = e[i].nxt)
      e1[u].push_back(Edge(e[i].v, e[i].w)),
          e2[e[i].v].push_back(Edge(u, e[i].w));
  Dijkstra(1);
  int ans = 0;
  for (int i = 1; i <= k; ++i)
    ans = (ans + Solve(1, i)) % p;
  printf("%d\n", ans);
}
}  // namespace Subtask2

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    memset(head, 0, sizeof(head));
    edge_cnt = 0;
    scanf("%d%d%d%d", &n, &m, &k, &p);
    for (int i = 1, u, v, w; i <= m; ++i) {
      scanf("%d%d%d", &u, &v, &w);
      AddEdge(u, v, w);
    }
    if (k == 0) {
      Subtask1::Main();
    } else {
      Subtask2::Main();
    }
  }
  return 0;
}
