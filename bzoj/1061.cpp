#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e5 + 10;
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

int a[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int s = n + m + 1, t = s + 1;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    AddEdge(i, i + 1, INF - a[i], 0);
    AddEdge(i + 1, i, 0, 0);
  }
  AddEdge(s, 1, INF, 0), AddEdge(1, s, 0, 0);
  AddEdge(n + 1, t, INF, 0), AddEdge(t, n + 1, 0, 0);
  for (int i = 1, x, y, c; i <= m; i++) {
    scanf("%d%d%d", &x, &y, &c);
    AddEdge(x, y + 1, INF, c);
    AddEdge(y + 1, x, 0, -c);
  }
  Mcmf(s, t);
  printf("%d\n", mincost);
  return 0;
}
