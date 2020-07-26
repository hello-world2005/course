#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

const int N = 4e5 + 10;
const int M = 8e5 + 10;

int n, m;

// ========== Dijkstra ==========

struct Edge {
  int v, w, nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[M << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int dis[N], vis[N];

typedef std::pair<int, int> pii;

struct Node {
  int v, w;

  Node() : v(0), w(0) {}
} p[N << 1];

void Dijkstra(int s) {
  memset(dis, 0x3f, sizeof(dis));
  memset(vis, false, sizeof(vis));
  std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
  dis[s] = 0;
  q.push(std::make_pair(0, s));
  while (!q.empty()) {
    auto tp = q.top();
    q.pop();
    int u = tp.second;
    if (vis[u])
      continue;
    vis[u] = true;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].w;
      if (vis[v])
        continue;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        q.push(std::make_pair(dis[v], v));
      }
    }
  }
  for (int i = 1; i <= n; ++i)
    p[i].w = dis[i];
#ifdef DEBUG
  printf("\n==========\n");
  for (int i = 1; i <= n; ++i)
    printf("%d ", dis[i]);
  printf("\n==========\n");
#endif
}

// ========== Kruskal ==========

struct E {
  int u, v, l, a;

  E() : u(0), v(0), l(0), a(0) {}
  E(int _u, int _v, int _l, int _a) : u(_u), v(_v), l(_l), a(_a) {}
};
std::vector<E> edge;
struct Ed {
  int v, nxt;

  Ed() : v(0), nxt(0) {}
  Ed(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} ed[N << 1];
int he[N << 1], ed_cnt;

void AddEdge(int u, int v) {
  ed[++ed_cnt] = Ed(v, he[u]);
  he[u] = ed_cnt;
}

int fa[N << 1];

int FindFa(int u) {
  if (u == fa[u])
    return u;
  return fa[u] = FindFa(fa[u]);
}

void Kruskal() {
  std::sort(edge.begin(), edge.end(),
            [&](const E lhs, const E rhs) { return lhs.a > rhs.a; });
  int cnt = n, tot = 0;
  for (auto i : edge) {
    int u = i.u, v = i.v, fu = FindFa(u), fv = FindFa(v);
    if (fu != fv) {
      fa[fu] = fa[fv] = ++cnt;
      AddEdge(cnt, fu), AddEdge(cnt, fv);
      p[cnt].v = i.a;
      ++tot;
    }
    if (tot == n - 1)
      break;
  }
}

// ========== Main ==========

int dep[N], f[N][20];

void Dfs(int u, int fa) {
  dep[u] = dep[fa] + 1;
  f[u][0] = fa;
  for (int i = 1; i < 20; ++i)
    f[u][i] = f[f[u][i - 1]][i - 1];
#ifdef DEBUG
  printf("u: %d\n", u);
#endif
  for (int i = he[u]; i; i = ed[i].nxt) {
    int v = ed[i].v;
    Dfs(v, u);
    p[u].w = std::min(p[u].w, p[v].w);
  }
}

int Solve(int s, int v) {
  for (int i = 19; i >= 0; --i)
    if ((1 << i) < dep[s] && p[f[s][i]].v > v)
      s = f[s][i];
#ifdef DEBUG
  printf("s: %d %d\n", s, dep[s]);
#endif
  return p[s].w;
}

void Init() {
  memset(head, 0, sizeof(head));
  memset(he, 0, sizeof(he));
  edge_cnt = ed_cnt = 0;
  edge.clear();
  memset(dep, 0, sizeof(dep));
  memset(f, 0, sizeof(f));
  for (int i = 1; i <= 2 * n; ++i)
    fa[i] = i;
  memset(p, 0, sizeof(p));
  for (int i = 1; i <= 2 * n; ++i)
    p[i].w = 0x3f3f3f3f;
}

int main() {
  freopen("return.in", "r", stdin);
  freopen("return.out", "w", stdout);
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    Init();
    for (int i = 1, u, v, l, a; i <= m; ++i) {
      scanf("%d%d%d%d", &u, &v, &l, &a);
      edge.push_back(E(u, v, l, a));
      AddEdge(u, v, l), AddEdge(v, u, l);
    }
    Dijkstra(1);
    Kruskal();
    Dfs(2 * n - 1, 0);
#ifdef DEBUG
    for (int i = 1; i <= 2 * n - 1; ++i)
      printf("p: %d %d\n", p[i].v, p[i].w);
#endif
    int last_ans = 0;
    int q, k, s;
    scanf("%d%d%d", &q, &k, &s);
    for (int i = 1, v, p; i <= q; ++i) {
      scanf("%d%d", &v, &p);
      v = (v + k * last_ans - 1) % n + 1, p = (p + k * last_ans) % (s + 1);
#ifdef DEBUG
      printf(">> %d %d\n", v, p);
#endif
      printf("%d\n", last_ans = Solve(v, p));
    }
  }
  return 0;
}
