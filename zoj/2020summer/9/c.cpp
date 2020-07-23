#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>

const int N = 310;

std::bitset<N> bs[N];
int deg[N];

std::bitset<N> d[N];

void Insert(int n, std::bitset<N> x) {
  for (int i = n - 1; i >= 0; --i) {
    if (x[i]) {
      if (d[i].count()) {
        x ^= d[i];
      } else {
        d[i] = x;
        break;
      }
    }
  }
}

bool Find(int n, std::bitset<N> x) {
  for (int i = n - 1; i >= 0; --i)
    if (x[i]) {
      if (d[i].count())
        x ^= d[i];
      else
        return false;
    }
  return true;
}

std::bitset<N> sta;
struct Edge {
  int v, w, nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, int _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[N * N << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v, int w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    sta.reset();
    for (int i = 0; i < N; ++i)
      bs[i].reset(), d[i].reset();
    memset(head, -1, sizeof(head));
    memset(deg, 0, sizeof(deg));
    edge_cnt = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= m; ++i) {
      scanf("%d%d%d", &u, &v, &w);
      --u, --v;
      ++deg[u], ++deg[v];
      sta[u] = sta[u] ^ w, sta[v] = sta[v] ^ w;
      AddEdge(u, v, w), AddEdge(v, u, w);
    }
    for (int u = 1; u <= n; ++u) {
      if (deg[u] & 1)
        bs[u][u] = true;
      for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v, w = e[i].w;
        bs[u][v] = true;
      }
      Insert(n, bs[u]);
    }
    printf("%s\n", Find(n, sta) ? "yes" : "no");
  }
  return 0;
}
