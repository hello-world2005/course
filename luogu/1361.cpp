#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

typedef long long ll;

const int N = 3010;
const int M = 2000010;
const ll INF = 100000000000000ll;

int n, m;
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

int a[N], b[N];
ll suma, sumb;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), suma += a[i];
  for (int i = 1; i <= n; ++i)
    scanf("%d", &b[i]), sumb += b[i];
  scanf("%d", &m);
  int s = 2 * m + n + 1, t = s + 1;
  for (int i = 1; i <= n; ++i) {
    AddEdge(s, m + i, a[i]);
    AddEdge(m + i, s, 0);
    AddEdge(m + i, t, b[i]);
    AddEdge(t, m + i, 0);
  }
  ll ans = 0;
  for (int i = 1, k, c1, c2; i <= m; ++i) {
    scanf("%d%d%d", &k, &c1, &c2);
    for (int j = 1, id; j <= k; ++j) {
      scanf("%d", &id);
      AddEdge(i, m + id, INF);
      AddEdge(m + id, i, 0);
      AddEdge(m + id, m + n + i, INF);
      AddEdge(m + n + i, m + id, 0);
    }
    AddEdge(s, i, c1);
    AddEdge(i, s, 0);
    AddEdge(m + n + i, t, c2);
    AddEdge(t, m + n + i, 0);
    ans += c1 + c2;
  }
  n = t;
  printf("%lld\n", suma + sumb + ans - Dinic(s, t));
  return 0;
}
