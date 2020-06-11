#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

typedef int ll;

const int N = 2010;
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

int a[N][N], v[N];

bool Check(int x) {
  int s = n + m + 1, t = n + m + 2;
  totn = t;
  for (int i = 1; i <= m - x + 1; ++i) {
    memset(head, 0, sizeof(head));
    edge_cnt = 0;
    for (int j = 1; j <= n; ++j) {
      AddEdge(s, j, 1);
      AddEdge(j, s, 0);
    }
    for (int j = 1; j <= m; ++j) {
      AddEdge(j + n, t, v[j]);
      AddEdge(t, j + n, 0);
    }
    for (int j = 1; j <= n; ++j)
      for (int k = i; k <= i + x - 1; ++k) {
        AddEdge(j, a[j][k] + n, 1);
        AddEdge(a[j][k] + n, j, 0);
      }
    if (Dinic(s, t) == n)
      return false;
  }
  return true;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      scanf("%d", &a[i][j]);
  for (int i = 1; i <= m; ++i)
    scanf("%d", &v[i]);
  int l = 1, r = m, ans = 0;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (Check(mid)) {
      l = mid + 1;
    } else {
      r = mid - 1;
      ans = mid;
    }
  }
  printf("%d\n", ans);
  return 0;
}
