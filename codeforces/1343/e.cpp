#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

typedef long long ll;

const int N = 2e5 + 10;

int w[N];
int n;

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

int dis[N], dist[N][4];
bool vis[N];

void Dijkstra(int s, int id) {
  memset(vis, false, sizeof(vis));
  memset(dis, 0x3f, sizeof(dis));
  std::priority_queue<std::pair<int, int> > q;
  q.push(std::make_pair(0, s));
  dis[s] = 0;
  while (!q.empty()) {
    int u = q.top().second;
    q.pop();
    if (vis[u])
      continue;
    vis[u] = true;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = 1;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + 1;
        q.push(std::make_pair(-dis[v], v));
      }
    }
  }
  for (int i = 1; i <= n; ++i)
    dist[i][id] = dis[i];
}

ll s[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int m, a, b, c;
    scanf("%d%d%d%d%d", &n, &m, &a, &b, &c);
    for (int i = 1; i <= m; ++i)
      scanf("%d", &w[i]);
    for (int i = 1, u, v; i <= m; ++i) {
      scanf("%d%d", &u, &v);
      AddEdge(u, v), AddEdge(v, u);
    }
    Dijkstra(a, 1), Dijkstra(b, 2), Dijkstra(c, 3);
    std::sort(w + 1, w + m + 1);
    for (int i = 1; i <= m; ++i)
      s[i] = s[i - 1] + w[i];
    ll ans = 1e16;
    for (int i = 1; i <= n; ++i) {
      ll now = s[dist[i][1] + dist[i][2] + dist[i][3]] + s[dist[i][2]];
      if (dist[i][1] + dist[i][2] + dist[i][3] <= m)
        ans = std::min(ans, now);
      // printf("> %d %d\n", now, i);
    }
    printf("%lld\n", ans);
    for (int i = 1; i <= n; ++i)
      head[i] = 0;
    edge_cnt = 0;
  }
  return 0;
}
