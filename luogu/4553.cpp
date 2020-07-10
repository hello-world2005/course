#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>

const int N = 1e4 + 10;
const int M = 1e6 + 10;
const int INF = 0x3f3f3f3f;

struct Edge {
  int v, w, f, nxt;

  Edge() : v(0), w(0), f(0), nxt(0) {}
  Edge(int _v, int _w, int _f, int _nxt) : v(_v), w(_w), f(_f), nxt(_nxt) {}
} e[M];
int head[N], edge_cnt = 1;

void AddEdge(int u, int v, int w, int f) {
  e[++edge_cnt] = Edge(v, w, f, head[u]);
  head[u] = edge_cnt;
}

int d[N];

void AddEdge(int u, int v, int l, int r, int f) {
  AddEdge(u, v, r - l, f);
  AddEdge(v, u, 0, -f);
  d[u] -= l;
  d[v] += l;
}

int cur[N];
int dis[N];
bool vis[N];

bool Spfa(int s, int t) {
  memset(dis, 0x3f, sizeof(dis));
  memset(vis, false, sizeof(vis));
  memcpy(cur, head, sizeof(head));
  std::queue<int> q;
  q.push(s);
  dis[s] = 0;
  vis[s] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
#ifdef DEBUG
    printf("%d\n", u);
#endif
    vis[u] = false;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].f;
      if (dis[v] > dis[u] + w && e[i].w) {
        dis[v] = dis[u] + w;
        if (!vis[v])
          q.push(v), vis[v] = true;
      }
    }
  }
  return dis[t] < 0x3f3f3f3f;
}

int maxflow, mincost;

int Dfs(int u, int flow, int t) {
  vis[u] = true;
  if (u == t) {
    maxflow += flow;
    return flow;
  }
  int res = 0;
  for (int i = cur[u]; i; i = e[i].nxt) {
    cur[u] = i;
    int v = e[i].v, w = e[i].f;
    if (dis[v] == dis[u] + w && e[i].w && (v == t || !vis[v])) {
      int now = Dfs(v, std::min(e[i].w, flow - res), t);
      if (now) {
        e[i].w -= now;
        e[i ^ 1].w += now;
        mincost += now * w;
        res += now;
        if (res == flow)
          break;
      }
    }
  }
  return res;
}

void Mcmf(int s, int t) {
  while (Spfa(s, t)) {
    vis[t] = true;
    while (vis[t]) {
      memset(vis, false, sizeof(vis));
      Dfs(s, INF, t);
    }
  }
}

int a[N], c[N][N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j)
      scanf("%d", &c[i][j]);
  int s = n * 2 + 1, t = s + 1, S = t + 2, T = S + 1;
  for (int i = 1; i <= n; ++i) {
    AddEdge(s, i, 0, m, 0);
    AddEdge(i, i + n, a[i], a[i], 0);
    AddEdge(i + n, t, 0, m, 0);
    for (int j = i + 1; j <= n; ++j)
      if (~c[i][j])
        AddEdge(i + n, j, 0, m, c[i][j]);
  }
  AddEdge(t, t + 1, m, m, 0);
  for (int i = 1; i <= t + 1; ++i) {
    if (d[i] > 0)
      AddEdge(S, i, d[i], 0), AddEdge(i, S, 0, 0);
    else if (d[i] < 0)
      AddEdge(i, T, -d[i], 0), AddEdge(T, i, 0, 0);
  }
  AddEdge(t + 1, s, 0, INF, 0);
  Mcmf(S, T);
#ifdef DEBUG
  printf("%d\n", maxflow);
#endif
  printf("%d\n", mincost);
  return 0;
}
