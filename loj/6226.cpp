#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

typedef int ll;

const int N = 40010;
const int M = 4000010;
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

int g[210][210];

const int DX[] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int DY[] = {-1, 1, -2, 2, -2, 2, -1, 1};

int F(int x, int y) {
  return n * (x - 1) + y;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, x, y; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    g[x][y] = 1;
  }
  int s = n * n + 1, t = s + 1;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      if (!g[i][j]) {
        if ((i + j) & 1) {
          AddEdge(s, F(i, j), 1);
          AddEdge(F(i, j), s, 0);
          for (int k = 0; k < 8; ++k) {
            int _i = i + DX[k], _j = j + DY[k];
            if (_i < 1 || _i > n || _j < 1 || _j > n || g[_i][_j])
              continue;
            AddEdge(F(i, j), F(_i, _j), INF);
            AddEdge(F(_i, _j), F(i, j), 0);
          }
        } else {
          AddEdge(F(i, j), t, 1);
          AddEdge(t, F(i, j), 0);
        }
      }
  totn = t;
  printf("%d\n", n * n - m - Dinic(s, t));
  return 0;
}
