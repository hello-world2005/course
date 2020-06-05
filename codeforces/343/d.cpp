#include <cstdio>
#include <set>
#include <vector>

const int N = 5e5 + 10;

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

void GetSze(int u, int fa) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    GetSze(v, u);
    sze[u] += sze[v];
    if (sze[s[u]] < sze[v])
      s[u] = v;
  }
}

std::vector<std::pair<int, int> > ope[N];
std::vector<int> que[N];
int ans[N];
std::set<std::pair<int, int> > now1;

void Add(int u, int fa, bool flag) {
  for (auto i : ope[u])
    if (i.second == 0)
      if (flag)
        now1.insert(i);
      else
        now1.erase(i);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa)
      continue;
    Add(v, u, flag);
  }
}

void Dfs(int u, int fa, bool flag) {
  for (auto i : ope[u])
    if (~i.first)
      now1.insert(i);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa || v == s[u])
      continue;
    Dfs(v, u, false);
    Add(v, u, false);
  }
  if (s[u]) {
    Dfs(s[u], u, true);
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v;
      if (v == fa || v == s[u])
        continue;
      Add(v, u, true);
    }
  }
  for (auto i : ope[u])
    if (i.first == -1)
      now1.insert(i);
  
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v);
    AddEdge(v, u);
  }
  GetSze(1, 0);
  scanf("%d", &q);
  for (int i = 1, opt, u; i <= q; ++i) {
    scanf("%d%d", &opt, &u);
    if (opt == 1)
      ope[u].push_back(std::make_pair(1, i));
    else if (opt == 2)
      ope[u].push_back(std::make_pair(-1, i));
    else
      que[u].push_back(i);
  }
  Dfs(1, 0, false);
}
