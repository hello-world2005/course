#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

const int N = 1e5 + 10;
const int M = 4e5 + 10;

struct Edge {
  int v, w, nxt;
  bool kind;

  Edge()
      : v(0), w(0), nxt(0), kind(false) {}
  Edge(int _v, int _w, int _nxt, int _kind)
      : v(_v), w(_w), nxt(_nxt), kind(_kind) {}
} e[M << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v, int w, int kind) {
  e[++edge_cnt] = Edge(v, w, head[u], kind);
  head[u] = edge_cnt;
}

int ans;

bool vis[N], qwq[N];
int dis[N];

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1, u, v, w; i <= m; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    AddEdge(u, v, w, false), AddEdge(v, u, w, false);
  }
  memset(dis, 0x3f, sizeof(dis));
  std::vector<int> vec;
  std::priority_queue<std::pair<int, int> > q;
  for (int i = 1, v, w; i <= k; ++i) {
    scanf("%d%d", &v, &w);
    if (dis[v] != 0x3f3f3f3f)
      ++ans;
    dis[v] = std::min(dis[v], w);
  }
  for (int i = 1; i <= n; ++i)
    if (dis[i] != 0x3f3f3f3f)
      q.push(std::make_pair(-dis[i], i)), vec.push_back(i);
  memset(vis, false, sizeof(vis));
  q.push(std::make_pair(0, 1)), dis[1] = 0;
  while (!q.empty()) {
    int u = q.top().second;
    // printf("%d\n")
    q.pop();
    if (vis[u])
      continue;
    vis[u] = true;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].w;
      if (dis[v] >= dis[u] + w)
        dis[v] = dis[u] + w, q.push(std::make_pair(-dis[v], v)), qwq[v] = true;
    }
  }
  for (int i : vec)
    if (qwq[i])
      ++ans;
  printf("%d\n", ans);
  return 0;
}
