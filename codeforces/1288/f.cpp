#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 410;
const int M = N * N;
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

char s1[N], s2[N];

int main() {
  int n1, n2, m, r, b;
  scanf("%d%d%d%d%d", &n1, &n2, &m, &r, &b);
  scanf("%s%s", s1 + 1, s2 + 1);
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v + n1, 0, 1, r);
    AddEdge(v + n1, u, 0, 1, b);
  }
  int s = n1 + n2 + 1, t = s + 1, S = s + 2, T = t + 2;
  for (int i = 1; i <= n1; ++i) {
    if (s1[i] == 'R')
      AddEdge(s, i, 1, INF, 0);
    else if (s1[i] == 'B')
      AddEdge(i, t, 1, INF, 0);
    else
      AddEdge(s, i, 0, INF, 0), AddEdge(i, t, 0, INF, 0);
  }
  for (int i = 1; i <= n2; ++i) {
    if (s2[i] == 'B')
      AddEdge(s, i + n1, 1, INF, 0);
    else if (s2[i] == 'R')
      AddEdge(i + n1, t, 1, INF, 0);
    else
      AddEdge(s, i + n1, 0, INF, 0), AddEdge(i + n1, t, 0, INF, 0);
  }
  int sum = 0;
  for (int i = 1; i <= t; ++i) {
    if (d[i] > 0)
      AddEdge(S, i, d[i], 0), AddEdge(i, S, 0, 0), sum += d[i];
    else if (d[i] < 0)
      AddEdge(i, T, -d[i], 0), AddEdge(T, i, 0, 0);
  }
  AddEdge(t, s, 0, INF, 0);
  Mcmf(S, T);
  if (maxflow != sum)
    return printf("-1"), 0;
  printf("%d\n", mincost);
  for (int i = 2; i <= m * 4; i += 4)
    if (!e[i].w)
      printf("R");
    else if (!e[i + 2].w)
      printf("B");
    else
      printf("U");
  return 0;
}
