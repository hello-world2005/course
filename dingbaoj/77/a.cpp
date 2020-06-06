#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <climits>

typedef long long ll;

const int N = 10010;
const int M = 200010;
const ll INF = 100000000000000ll;

int n;
struct Edge {
  int v;
  ll w;
  int nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, ll _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[M];
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

// std::vector<int> idx[N];
int idx[110][30];

signed main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d", &n);
    int s = 1, t = 2;
    int cnt = 2;
    ll sum = 0;
    memset(e, 0, sizeof(e));
    memset(head, 0, sizeof(head));
    edge_cnt = 0;
    for (int i = 1, m; i <= n; ++i) {
      scanf("%d", &m);
      // idx[i].resize(m + 1);
      for (int j = 1, w; j <= m; ++j) {
        ll c, v;
        scanf("%lld%lld%d", &c, &v, &w);
        idx[i][j] = ++cnt;
        ll f = v - c;
        if (f > 0)
          AddEdge(s, idx[i][j], f), AddEdge(idx[i][j], s, 0), sum += f;
        if (f < 0)
          AddEdge(idx[i][j], t, -f), AddEdge(t, idx[i][j], 0);
        for (int k = 1, a, b; k <= w; ++k) {
          scanf("%d%d", &a, &b);
          AddEdge(idx[i][j], idx[a][b], INF);
          AddEdge(idx[a][b], idx[i][j], 0);
        }
      }
    }
    n = cnt;
    printf("Case #%d: %lld\n", cas, sum - Dinic(s, t));
  }
  return 0;
}
