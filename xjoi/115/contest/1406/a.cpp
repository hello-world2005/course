#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1010;

int n1, n2, m, v;
struct Edge {
  int v, nxt;

  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} e[N * N];
int head[N], edge_cnt;

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

int linker[N];
bool used[N];

bool Dfs(int u) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (used[v])
      continue;
    used[v] = true;
    if (linker[v] == -1 || Dfs(linker[v])) {
      linker[v] = u;
      return true;
    }
  }
  return false;
}

int Hungary() {
  memset(linker, -1, sizeof(linker));
  int res = 0;
  for (int i = 1; i <= n1; ++i) {
    memset(used, false, sizeof(used));
    if (Dfs(i))
      ++res;
  }
  return res;
}

int main() {
  scanf("%d%d%d%d", &v, &n1, &n2, &m);
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d%d", &u, &v);
    AddEdge(u, v + n1);
    AddEdge(v + n1, u);
  }
  printf("%d\n", std::min(v + 1, n1 + n2 - Hungary()));
  return 0;
}
