#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>

const int N = 2000;
const int M = 100000;
const double EPS = 1e-5;
const int INF = 0x3f3f3f3f;

int n, m;
struct Edge {
  int v;
  double w;
  int nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, double _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[M << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v, double w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int dep[N];
int totn, cur[N];

bool Bfs(int s, int t) {
  for (int i = 0; i <= totn; ++i)
    cur[i] = head[i];
  memset(dep, 0, sizeof(dep));
  std::queue<int> q;
  dep[s] = 1;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v;
      double w = e[i].w;
      if (w < EPS || dep[v])
        continue;
      dep[v] = dep[u] + 1;
      q.push(v);
    }
  }
  return dep[t] > 0;
}

double Dfs(int u, double val, int t) {
  if (u == t || val < EPS)
    return val;
  double res = 0, now;
  for (int i = cur[u]; i; i = e[i].nxt) {
    cur[u] = i;
    int v = e[i].v;
    double w = e[i].w;
    if (dep[v] != dep[u] + 1 || (now = Dfs(v, std::min(val, w), t)) < EPS)
      continue;
    e[i].w -= now;
    e[i ^ 1].w += now;
    val -= now;
    res += now;
    if (val < EPS)
      break;
  }
  return res;
}

double Dinic(int s, int t) {
  double res = 0;
  while (Bfs(s, t)) {
    res += Dfs(s, INF, t);
    // printf("%.4f\n", res);
  }
  return res;
}

std::vector<std::pair<int, int> > edge;
int deg[N];

double Check(double x) {
  memset(head, 0, sizeof(head));
  edge_cnt = 1;
  int s = n + 1, t = n + 2;
  for (auto i : edge) {
    AddEdge(i.first, i.second, 1);
    AddEdge(i.second, i.first, 0);
    AddEdge(i.second, i.first, 1);
    AddEdge(i.first, i.second, 0);
  }
  for (int i = 1; i <= n; ++i) {
    AddEdge(s, i, m);
    AddEdge(i, s, 0);
    AddEdge(i, t, m + 2 * x - deg[i]);
    AddEdge(t, i, 0);
  }
  totn = n + 2;
  int res = Dinic(s, t);
  return (m * n - res) / 2.0;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d%d", &u, &v);
    ++deg[u], ++deg[v];
    edge.push_back(std::make_pair(u, v));
  }
  double l = 0, r = 1000;
  while (fabs(l - r) > EPS) {
    double mid = (l + r) / 2;
    // printf("%.5f %.5f\n", l, r);
    if (Check(mid) > EPS)
      l = mid;
    else
      r = mid;
  }
  printf("%.4f\n", l);
  return 0;
}
