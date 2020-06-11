#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

typedef int ll;

const int N = 55010;
const int M = 6000010;
const ll INF = 100000000;

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
 
int main() {
  scanf("%d%d", &n, &m);
  int s = n + m + 1, t = s + 1;
  for (int i = 1, p; i <= n; ++i) {
    scanf("%d", &p);
    AddEdge(s, i, p);
    AddEdge(i, s, 0);
  }
  ll sum = 0;
  for (int i = 1, a, b, c; i <= m; ++i) {
    scanf("%d%d%d", &a, &b, &c);
    AddEdge(n + i, t, c);
    AddEdge(t, n + i, 0);
    AddEdge(a, n + i, INF);
    AddEdge(n + i, a, 0);
    AddEdge(b, n + i, INF);
    AddEdge(n + i, b, 0);
    sum += c;
  }
  n = t;
  printf("%lld\n", sum - Dinic(s, t));
  return 0;
}
