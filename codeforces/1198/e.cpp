#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

typedef long long ll;

const int N = 410;
const int M = N * N;
const ll INF = 100000000000000ll;

struct Point {
  int x, y;

  Point() : x(0), y(0) {}
};

int n, m;
struct Square {
  Point p1, p2;

  Square() : p1(), p2() {}
} a[N];
std::vector<int> x, y;

struct Edge {
  int v;
  ll w;
  int nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, ll _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[M << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v, ll w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int dep[N];
int cur[N];

ll Dfs(int u, ll val, int t) {
  if (u == t)
    return val;
  ll res = 0;
  for (int i = cur[u]; i && val; i = e[i].nxt) {
    cur[u] = i;
    int v = e[i].v;
    ll w = e[i].w;
    if (!w || dep[v] != dep[u] + 1)
      continue;
    ll now = Dfs(v, std::min(val, w), t);
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

ll Dinic(int s, int t) {
  ll res = 0;
  while (Bfs(s, t))
    res += Dfs(s, INF, t);
  return res;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d%d%d", &a[i].p1.x, &a[i].p1.y, &a[i].p2.x, &a[i].p2.y);
    ++a[i].p2.x, ++a[i].p2.y;
    x.push_back(a[i].p1.x), x.push_back(a[i].p2.x);
    y.push_back(a[i].p1.y), y.push_back(a[i].p2.y);
  }
  x.push_back(n + 1);
  y.push_back(n + 1);
  std::sort(x.begin(), x.end());
  std::sort(y.begin(), y.end());
  x.erase(std::unique(x.begin(), x.end()), x.end());
  y.erase(std::unique(y.begin(), y.end()), y.end());
  for (int i = 1; i <= m; ++i) {
    int x1 = std::lower_bound(x.begin(), x.end(), a[i].p1.x) - x.begin() + 1;
    int y1 = std::lower_bound(y.begin(), y.end(), a[i].p1.y) - y.begin() + 1;
    int x2 = std::lower_bound(x.begin(), x.end(), a[i].p2.x) - x.begin() + 1;
    int y2 = std::lower_bound(y.begin(), y.end(), a[i].p2.y) - y.begin() + 1;
    // printf("%d %d %d %d\n", x1, y1, x2, y2);
    for (int i = x1; i < x2; ++i)
      for (int j = y1; j < y2; ++j)
        AddEdge(i, j + x.size(), INF), AddEdge(j + x.size(), i, 0);
  }
  int s = x.size() + y.size() + 1, t = s + 1;
  // printf("%u %u %d %d\n", x.size(), y.size(), s, t);
  for (int i = 0; i < (int)x.size() - 1; ++i)
    AddEdge(s, i + 1, x[i + 1] - x[i]), AddEdge(i + 1, s, 0);
  for (int i = 0; i < (int)y.size() - 1; ++i)
    AddEdge(i + x.size() + 1, t, y[i + 1] - y[i]),
        AddEdge(t, i + x.size() + 1, 0);
  n = t;
  // for (int u = 1; u <= n; ++u)
  //   for (int i = head[u]; i; i = e[i].nxt)
  //     if (e[i].w)
  //     printf("%d %d %lld\n", u, e[i].v, e[i].w);
  printf("%lld\n", Dinic(s, t));
  return 0;
}
