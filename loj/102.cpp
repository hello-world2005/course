#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

const int N = 410;
const int M = 15010;
const int INF = 0x7fffffff;

int n, m;
struct Edge {
  int v, w, f, nxt;

  Edge() : v(0), w(0), f(0), nxt(0) {}
  Edge(int _v, int _w, int _f, int _nxt) : v(_v), w(_w), f(_f), nxt(_nxt) {}
} e[M << 1];
int head[N], edge_cnt = 1;

void AddEdge(int u, int v, int w, int f) {
  e[++edge_cnt] = Edge(v, w, f, head[u]);
  head[u] = edge_cnt;
}

int dis[N], h[N];
int idxv[N], idxe[N];

typedef std::pair<int, int> pii;

bool Dijkstra(int s, int t) {
  std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
  memset(dis, -1, sizeof(dis));
  dis[s] = 0;
  q.push(std::make_pair(0, s));
  while (!q.empty()) {
    auto tp = q.top();
    q.pop();
    int u = tp.second;
    if (dis[u] < tp.first)
      continue;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].f;
      if (!e[i].w)
        continue;
      // printf("%d %d\n", i, e[i].w);
      if (dis[v] < 0 || dis[v] > dis[u] + w + h[u] - h[v]) {
        dis[v] = dis[u] + w + h[u] - h[v];
        idxv[v] = u;
        idxe[v] = i;
        // printf("%d %d %d %d\n", u, v, dis[v], e[i].w);
        q.push(std::make_pair(dis[v], v));
      }
    }
  }
  // for (int i = 1; i <= n; ++i)
  //   printf("%d ", dis[i]);
  // printf("\n");
  return dis[t] >= 0;
}

std::pair<int, int> Mcmf(int s, int t) {
  int res1 = 0, res2 = 0, f = INF;
  while (Dijkstra(s, t)) {
    for (int i = 1; i <= n; ++i)
      h[i] += (dis[i] == -1) ? 0 : dis[i];
    // printf("\n");
    int d = f;
    for (int u = t; u != s; u = idxv[u])
      d = std::min(d, e[idxe[u]].w);
    // printf("%d\n", d);
    // printf("==========\n");
    f -= d;
    res1 += d;
    res2 += h[t] * d;
    for (int u = t; u != s; u = idxv[u]) {
      e[idxe[u]].w -= d;
      e[idxe[u] ^ 1].w += d;
      // printf("%d %d %d\n", idxe[u], e[idxe[u]].v, e[idxe[u]].w);
    }
  }
  return std::make_pair(res1, res2);
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v, w, f; i <= m; ++i) {
    scanf("%d%d%d%d", &u, &v, &w, &f);
    AddEdge(u, v, w, f);
    AddEdge(v, u, 0, -f);
  }
  auto ans = Mcmf(1, n);
  printf("%d %d\n", ans.first, ans.second);
  return 0;
}

// 1 7 6
// 1 6 5
// 1 6 4
// 1 5 3
// 1 4 2
// 1 3 1
// 3 2 1
// 3 8 1
// 0 1 1 2 3 4 6 1
// 0 1 1 2 3 4 6 1
// 3 1
// ==========
// 1 7 0
// 1 6 1
// 1 6 0
// 1 5 0
// 1 4 0
// 1 3 -2
// 3 2 -2
// 3 8 -2
// 3 8 -2
// 3 6 -1
// 3 5 -1
// 2 8 -2
// 2 4 -1
// 2 3 -1
// 3 2 -1
// 3 8 -1
// 3 8 -1
// 3 6 0
// 3 5 0
// 2 8 -1
// 2 4 0
// 2 3 0
// 4 2 1
// 4 8 1
// 3 2 0
// 3 8 0
// 0 0 0 0 0 0 0 0
// 0 1 1 2 3 4 6 1
// 3 2
