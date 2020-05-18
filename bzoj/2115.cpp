#include <algorithm>
#include <cstdio>

#define int long long

const int N = 5e4 + 10;
const int M = 1e5 + 10;
const int K = 64;

int n, m;
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

int d[K];

bool Insert(int k) {
  for (int i = 60; i >= 0; --i)
    if (k >> i & 1ll) {
      if (d[i]) {
        k ^= d[i];
      } else {
        d[i] = k;
        return true;
      }
    }
  return false;
}

int p[N];

int Query(int k) {
  int ans = k;
  for (int i = 60; i >= 0; --i)
    ans = std::max(ans, ans ^ d[i]);
  return ans;
}

bool vis[N];

void Dfs(int u, int sum) {
  vis[u] = true;
  p[u] = sum;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v, w = e[i].w;
    if (vis[v])
      Insert(p[v] ^ sum ^ w);
    else
      Dfs(v, sum ^ w);
  }
}

signed main() {
  scanf("%lld%lld", &n, &m);
  for (int i = 1, u, v, w; i <= m; ++i) {
    scanf("%lld%lld%lld", &u, &v, &w);
    AddEdge(u, v, w);
    AddEdge(v, u, w);
  }
  Dfs(1, 0);
  printf("%lld\n", Query(p[n]));
  return 0;
}
