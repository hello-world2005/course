#include <cstdio>
#include <map>
#include <set>

const int N = 1e6 + 10;

int n;
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

int cnt[N];
// std::map<int, int> um;
std::set<std::pair<int, int> > um;
int ans[N];

void Dfs(int u, int fa, bool flag) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa || v == s[u])
      continue;
    Dfs(v, u, false);
  }
  if (s[u])
    Dfs(s[u], u, true);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa || v == s[u])
      continue;
    for (int j = l[v]; j <= r[v]; ++j) {
      int vv = idx[j];
      int d = dep[vv];
      // printf("%d\n", d);
      um.erase(std::make_pair(-cnt[d], d));
      ++cnt[d];
      // um[-cnt[d]] = d;
      um.insert(std::make_pair(-cnt[d], d));
    }
  }
  int d = dep[u];
  um.erase(std::make_pair(-cnt[d], d));
  ++cnt[d];
  // um[-cnt[d]] = d;
  um.insert(std::make_pair(-cnt[d], d));
  ans[u] = um.begin()->second - dep[u];
  // printf("%d: %d\n", u, um.begin()->second);
  if (!flag) {
    for (int i = l[u]; i <= r[u]; ++i)
      cnt[dep[idx[i]]] = 0;
    um.clear();
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v);
    AddEdge(v, u);
  }
  dep[1] = 1;
  GetSze(1, 0);
  Dfs(1, 0, false);
  for (int i = 1; i <= n; ++i)
    printf("%d\n", ans[i]);
  return 0;
}
