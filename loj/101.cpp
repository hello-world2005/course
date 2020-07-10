#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

#define int long long

const int N = 3010;
const int M = 100010;
const int INF = 0x3f3f3f3f;

int n, m, s, t;
struct Edge {
  int v, w, nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[M << 1];
int head[N], edge_cnt;
int a[N];

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int dep[N];
int cur[N];

int Dfs(int u, int val, int t) {
  if (u == t)
    return val;
  int res = 0;
  for (int &i = cur[u]; i && val; i = e[i].nxt) {
    int v = e[i].v, w = e[i].w;
    if (!w || dep[v] != dep[u] + 1)
      continue;
    int now = Dfs(v, std::min(val, w), t);
    e[i].w -= now;
    e[(i & 1) ? i + 1 : i - 1].w += now;
    val -= now;
    res += now;
  }
  if (res == 0)
    dep[u] = 0;
  return res;
}

bool Bfs(int s, int t) {
  for (int i = 1; i <= n; ++i)
    cur[i] = head[i];
  std::queue<int> q;
  memset(dep, 0, sizeof(dep));
  q.push(s);
  dep[s] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].w;
      if (!w || dep[v])
        continue;
      q.push(v);
      dep[v] = dep[u] + 1;
    }
  }
  return dep[t] > 0;
}

int Dinic() {
  int res = 0;
  while (Bfs(s, t))
    res += Dfs(s, INF, t);
  return res;
}

signed main() {
  scanf("%lld%lld%lld%lld", &n, &m, &s, &t);
  for (int i = 1, u, v, w; i <= m; ++i) {
    scanf("%lld%lld%lld", &u, &v, &w);
    AddEdge(u, v, w);
    AddEdge(v, u, 0);
  }
  printf("%lld\n", Dinic());
  return 0;
}
