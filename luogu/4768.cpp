#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

const int N = 2e5 + 10;
const int M = 4e5 + 10;

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

int dis[N];

typedef std::pair<int, int> pii;

void Dijkstra(int s) {
  memset(dis, 0x3f, sizeof(dis));
  std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
  q.push(std::make_pair(0, s));
  dis[s] = 0;
  while (!q.empty()) {
    auto tp = q.top();
    q.pop();
    int u = tp.second;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v, w = e[i].w;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        q.push(std::make_pair(dis[v], v));
      }
    }
  }
}

// ========== Kruskal ==========

// ========== Main ==========

struct E {
  int u, v, l, a;

  E() : u(0), v(0), l(0), a(0) {}
  E(int _u, int _v, int _l, int _a) : u(_u), v(_v), l(_l), a(_a) {}
};
std::vector<E> edge;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v, l, a; i <= m; ++i) {
    scanf("%d%d%d%d", &u, &v, &l, &a);
    edge.push_back(E(u, v, l, a));
    AddEdge(u, v, a), AddEdge(v, u, a);
  }
  Dijkstra(1);
  int last_ans = 0;
  int q, k, s;
  scanf("%d%d%d", &q, &k, &s);
  for (int i = 1, s, p; i <= q; ++i) {
    scanf("%d%d", &s, &p);
    s = (s + k * last_ans - 1) % n + 1, p = (p + k * last_ans) % s + 1;
  }
}
