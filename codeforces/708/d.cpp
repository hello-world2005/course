#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

#define int long long

const int N = 110;
const int M = 1e6;
const int INF = 1e12;

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

signed main() {
  int n, m, sum = 0;
  scanf("%lld%lld", &n, &m);
  for (int i = 1, u, v, c, f; i <= m; ++i) {
    scanf("%lld%lld%lld%lld", &u, &v, &c, &f);
    // c >= f: f -> f'
    // 0 <= f' < f: at most f times
    // f < f' <= c: at most c - f times

    // c < f: f-> f'
    // 0 <= f' < c: at most c times
    // c < f' < f: at most f - c times
    if (f <= c) {
      AddEdge(v, u, 0, f, 1);
      AddEdge(u, v, 0, c - f, 1);
      AddEdge(u, v, 0, INF, 2);
    } else {
      sum += f - c;
      AddEdge(v, u, 0, c, 1);
      AddEdge(v, u, 0, f - c, 0);
      AddEdge(u, v, 0, INF, 2);
    }
    AddEdge(u, v, f, f, 0);
  }
  int s = 1, t = n, S = n + 1, T = n + 2;
  for (int i = 1; i <= n; ++i) {
    if (d[i] > 0)
      AddEdge(S, i, d[i], 0), AddEdge(i, S, 0, 0);
    else if (d[i] < 0)
      AddEdge(i, T, -d[i], 0), AddEdge(T, i, 0, 0);
  }
  AddEdge(t, s, 0, INF, 0);
  Mcmf(S, T);
  printf("%lld\n", sum + mincost);
  return 0;
}
