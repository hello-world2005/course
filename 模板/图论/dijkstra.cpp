#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e5 + 10;
const int M = 2e5 + 10;

struct Edge {
  int v, w, nxt;

  Edge()
      : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt)
      : v(_v), w(_w), nxt(_nxt) {}
} e[M];
int head[N], edge_cnt;

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int dis[N];
bool vis[N];

void Dijkstra(int s) {
  std::priority_queue<std::pair<int, int> > q;
  memset(dis, 0x3f, sizeof(dis));
  dis[s] = 0;
  q.push(std::make_pair(0, s));
  while (!q.empty()) {
    int u = q.top().second;
    q.pop();
    if (vis[u])
      continue;
    vis[u] = true;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].w;
      if (vis[v])
        continue;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        q.push(std::make_pair(-dis[v], v));
      }
    }
  }
}

int main() {
  int n, m, s;
  scanf("%d%d%d", &n, &m, &s);
  for (int i = 1, u, v, w; i <= m; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    AddEdge(u, v, w);
  }
  Dijkstra(s);
  for (int i = 1; i <= n; ++i)
    printf("%d ", dis[i]);
  printf("\n");
  return 0;
}
