#include <algorithm>
#include <cstdio>
#include <queue>

const int N = 1e5 + 10;
const int M = 2e5 + 10;

int n, m;
struct Edge {
  int v, w, nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[M];
int head[N], edge_cnt;

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int deg[N];

void TopSort() {
  std::queue<int> q;
  q.push(n);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v, w; i <= m; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    AddEdge(v, u, w);
    ++deg[u];
  }
  TopSort();
}
