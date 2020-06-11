#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

typedef int ll;

const int N = 410;
const int M = 50010;
const ll INF = 100000000;

int n, m, k;
struct Edge {
  int v;
  ll w;
  int nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, ll _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[M << 1];
int head[N], edge_cnt = 1;

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
    e[i ^ 1].w += now;
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

int s, t;
int c[N];
bool vis[N];

void Dfs(int u) {
  vis[u] = true;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (e[i].w && !vis[v])
      Dfs(v);
  }
}

int main() {
  scanf("%d%d%d%d", &n, &m, &s, &t);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &c[i]);
    AddEdge(i, i + n, c[i]);
    AddEdge(i + n, i, 0);
  }
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u + n, v, INF);
    AddEdge(v, u + n, 0);
    AddEdge(v + n, u, INF);
    AddEdge(u, v + n, 0);
  }
  t += n;
  totn = 2 * n;
  int res = Dinic(s, t);
  // printf("%d\n", res);
  Dfs(s);
  std::vector<int> ans;
  for (int i = 2; i <= edge_cnt; i += 2) {
    int u = e[i ^ 1].v;
    int v = e[i].v;
    if (vis[u] && !vis[v])
      ans.push_back(u);
  }
  std::sort(ans.begin(), ans.end());
  for (auto i : ans)
    printf("%d ", i);
  return 0;
}
