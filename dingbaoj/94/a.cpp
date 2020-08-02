#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

#define int long long

const int N = 2e5 + 10;
const int M = 4e5 + 10;
const int K = 20;

struct Edge {
  int v, w, nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[M << 1];
int head[N], edge_cnt = 1;

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int fa[N], dfn[N], idx;
int col[N], color;
int ring[N], len[N];
int in_r[N];

void Paint(int u, int v) {
  // printf("%lld %lld\n", u, v);
  if (u == v)
    return;
  int i = fa[u];
  col[u] = color;
  AddEdge(v, u, 0);
  in_r[i] = in_r[i ^ 1] = 1;
  len[color] += e[i].w;
  Paint(e[i ^ 1].v, v);
}

int n, m, q;

void Dfs(int u, int fa) {
  // printf("%lld\n", u);
  dfn[u] = ++idx;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v, w = e[i].w;
    if (v == fa || i > m * 2 + 1)
      continue;
    if (!dfn[v]) {
      ring[v] = ring[u] + w;
      ::fa[v] = i;
      Dfs(v, u);
    } else if (dfn[v] < dfn[u]) {
      len[++color] = w;
      Paint(u, v);
    }
  }
}

int dep[N], f[N][K];

void Dfs2(int u) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v, w = e[i].w;
    if (!in_r[i] && !dep[v])
      f[v][0] = u, dep[v] = dep[u] + 1, Dfs2(v);
  }
}

int dis[N];

int Lca(int u, int v) {
  if (dep[u] < dep[v])
    std::swap(u, v);
  int x = u, y = v;
  for (int i = K - 1; i >= 0; --i)
    if (dep[f[u][i]] >= dep[v])
      u = f[u][i];
  if (u == v)
    return dis[x] - dis[y];
  for (int i = K - 1; i >= 0; --i)
    if (f[u][i] != f[v][i])
      u = f[u][i], v = f[v][i];
  if (col[u] && col[u] == col[v]) {
    int t = abs(ring[u] - ring[v]);
    return dis[x] - dis[u] + dis[y] - dis[v] + std::min(t, len[col[u]] - t);
  }
  return dis[x] + dis[y] - 2 * dis[f[u][0]];
}

bool in_que[N];

void Spfa() {
  memset(dis, 0x3f, sizeof(dis));
  std::queue<int> q;
  q.push(1);
  dis[1] = 0, in_que[1] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    in_que[u] = false;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].w;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        q.push(v);
        in_que[v] = true;
      }
    }
  }
}

signed main() {
  scanf("%lld%lld%lld", &n, &m, &q);
  for (int i = 1, u, v, w; i <= m; ++i) {
    scanf("%lld%lld%lld", &u, &v, &w);
    AddEdge(u, v, w), AddEdge(v, u, w);
  }
  Spfa();
  // printf("!");
  Dfs(1, 0);
  // printf("@");
  dep[1] = 1, Dfs2(1);
  for (int j = 1; j < K; ++j)
    for (int i = 1; i <= n; ++i)
      f[i][j] = f[f[i][j - 1]][j - 1];
  while (q--) {
    int u, v;
    scanf("%lld%lld", &u, &v);
    printf("%lld\n", Lca(u, v));
  }
  return 0;
}
