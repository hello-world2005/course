#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 4e5 + 10;

typedef long long ll;

ll a[N];
struct Edge {
  int v;
  ll w;
  int nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, ll _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v, ll w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

ll dis[N];
bool vis[N];

void Dijkstra(int s) {
  memset(dis, 0x3f, sizeof(dis));
  memset(vis, false, sizeof(vis));
  std::priority_queue<std::pair<ll, int> > q;
  dis[s] = 0;
  q.push(std::make_pair(dis[s], s));
  while (!q.empty()) {
    int u = q.top().second;
    q.pop();
    if (vis[u])
      continue;
    vis[u] = true;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v;
      ll w = e[i].w;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        q.push(std::make_pair(-dis[v], v));
      }
    }
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v; i <= m; ++i) {
    ll w;
    scanf("%d%d%lld", &u, &v, &w);
    AddEdge(u, v, w << 1), AddEdge(v, u, w << 1);
  }
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]);
  for (int i = 1; i <= n; ++i)
    AddEdge(n + 1, i, a[i]);
  Dijkstra(n + 1);
  for (int i = 1; i <= n; ++i)
    printf("%lld ", dis[i]);
  printf("\n");
  return 0;
}
