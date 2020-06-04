#include <cstdio>
#include <vector>

const int N = 1e6 + 10;

int n, q;
struct Edge {
  int v, nxt;

  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

int sze[N], s[N];
int dep[N];
int l[N], r[N], idx[N], ti_stamp;

void GetSze(int u, int fa) {
  sze[u] = 1;
  l[u] = ++ti_stamp;
  idx[ti_stamp] = u;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    dep[v] = dep[u] + 1;
    GetSze(v, u);
    sze[u] += sze[v];
    if (sze[s[u]] < sze[v])
      s[u] = v;
  }
  r[u] = ti_stamp;
}

int col[N];
int cnt[N];
int ans[N];
std::vector<std::pair<int, int> > que[N];
int d[N];
bool vis[N];

void Calc(int u, int fa, int c) {
  if (c == -1)
    d[cnt[col[u]]] += c;
  cnt[col[u]] += c;
  if (c == 1)
    d[cnt[col[u]]] += c;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa || vis[v])
      continue;
    Calc(v, u, c);
  }
}

void Dfs(int u, int fa, bool flag) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa || v == s[u])
      continue;
    Dfs(v, u, false);
  }
  if (s[u])
    Dfs(s[u], u, true), vis[s[u]] = true;
  Calc(u, fa, 1);
  for (auto i : que[u])
    ans[i.second] = d[i.first];
  vis[s[u]] = false;
  if (!flag)
    Calc(u, fa, -1);
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &col[i]);
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v);
    AddEdge(v, u);
  }
  for (int i = 1, u, k; i <= q; ++i) {
    scanf("%d%d", &u, &k);
    que[u].push_back(std::make_pair(k, i));
  }
  dep[1] = 1;
  GetSze(1, 0);
  Dfs(1, 0, false);
  for (int i = 1; i <= q; ++i)
    printf("%d\n", ans[i]);
  return 0;
}
