#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

typedef int ll;

const int N = 1010;
const int M = 6000010;
const ll INF = 100000000;

int n, m, k;
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
int cur[N], totn;

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
  for (int i = 1; i <= totn; ++i)
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

int g[N][N];
int h[N], r[N];

int f[N];

int FindFa(int u) {
  if (u == f[u])
    return u;
  return f[u] = FindFa(f[u]);
}

void Merge(int u, int v) {
  int fu = FindFa(u), fv = FindFa(v);
  if (fu != fv)
    f[fv] = fu;
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n + 2; ++i)
    f[i] = i;
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &h[i], &r[i]);
    for (int j = 0; j < r[i]; ++j) {
      scanf("%d", &g[i][j]);
      if (g[i][j] == 0)
        g[i][j] = n + 1;
      if (g[i][j] == -1)
        g[i][j] = n + 2;
      if (j != 0)
        Merge(g[i][j - 1], g[i][j]);
    }
  }
  if (FindFa(n + 1) != FindFa(n + 2)) {
    printf("0\n");
    return 0;
  }
  int ans = 0, res = 0;
  int s = N - 2, t = N - 1;
  for (ans = 1;; ++ans) {
    AddEdge(s, ans * (n + 1), INF);
    AddEdge(ans * (n + 1), s, 0);
    for (int i = 1; i <= m; ++i) {
      int u = (ans - 1) % r[i], v = ans % r[i];
      if (g[i][u] == n + 2)
        u = t;
      else
        u = (ans - 1) * (n + 1) + g[i][u];
      if (g[i][v] == n + 2)
        v = t;
      else
        v = ans * (n + 1) + g[i][v];
      // printf("%d %d\n", u, v);
      AddEdge(u, v, h[i]);
      AddEdge(v, u, 0);
    }
    totn = t;
    res += Dinic(s, t);
    // printf("%d %d\n", ans, res);
    if (res >= k) {
      printf("%d\n", ans);
      return 0;
    }
    for (int i = 1; i <= n + 1; ++i) {
      AddEdge((ans - 1) * (n + 1) + i, ans * (n + 1) + i, INF);
      AddEdge(ans * (n + 1) + i, (ans - 1) * (n + 1) + i, 0);
    }
  }
  return 0;
}
