#include <cstdio>
#include <vector>

const int N = 5e5 + 10;

int n, q;
char str[N];
struct Edge {
  int v, nxt;

  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} e[N];
int head[N], edge_cnt;
std::vector<std::pair<int, int> > que[N];

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

bool ans[N];

int dep[N], sze[N], s[N];
int l[N], r[N], idx[N], ti_stamp;

void GetSze(int u) {
  l[u] = ++ti_stamp;
  idx[ti_stamp] = u;
  sze[u] = 1;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    dep[v] = dep[u] + 1;
    GetSze(v);
    sze[u] += sze[v];
    if (sze[s[u]] < sze[v])
      s[u] = v;
  }
  r[u] = ti_stamp;
}

int cnt[N];

void AddP(int u, int v) {
  int c = str[u] - 'a', d = dep[u];
  cnt[d] ^= (1 << c);
}

void Add(int u, int v) {
  for (int i = l[u]; i <= r[u]; ++i)
    AddP(idx[i], v);
}

void Dfs(int u, bool flag) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == s[u])
      continue;
    Dfs(v, false);
    Add(v, -1);
  }
  if (s[u])
    Dfs(s[u], true);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == s[u])
      continue;
    Add(v, 1);
  }
  AddP(u, 1);
  // for (int i = head[u]; i; i = e[i].nxt) {
  //   int v = e[i].v;
  //   ans[que[v][i].second] = (cnt[que[v][i].])
  // }
  for (auto i : que[u])
    ans[i.second] = (cnt[i.first] == (cnt[i.first] & -cnt[i.first]));
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 2, f; i <= n; ++i) {
    scanf("%d", &f);
    AddEdge(f, i);
  }
  scanf("%s", str + 1);
  for (int i = 1; i <= q; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    que[a].push_back(std::make_pair(b, i));
  }
  dep[1] = 1;
  GetSze(1);
  Dfs(1, false);
  for (int i = 1; i <= q; ++i)
    printf("%s\n", ans[i] ? "Yes" : "No");
  return 0;
}
