#include <algorithm>
#include <cstdio>
#include <set>

const int N = 1e5 + 10;

struct Edge {
  int v, w, nxt;
  int idx;

  Edge() : v(0), w(0), nxt(0), idx(0) {}
  Edge(int _v, int _w, int _nxt, int _idx) : v(_v), w(_w), nxt(_nxt), idx(_idx) {}
} e[N << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v, int w, int i) {
  e[++edge_cnt] = Edge(v, w, head[u], i);
  head[u] = edge_cnt;
}

int sze[N];

void Dfs(int u, int fa) {
  int child = 0;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v, id = e[i].idx;
    if (id == fa)
      continue;
    ++child;
    Dfs(v, id);
    sze[fa] += sze[id];
  }
  if (!child)
    sze[fa] = 1;
}

int w[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    typedef long long ll;
    ll m;
    scanf("%d%lld", &n, &m);
    for (int i = 2, u, v, w; i <= n; ++i) {
      scanf("%d%d%d", &u, &v, &w);
      AddEdge(u, v, w, i), AddEdge(v, u, w, i);
      ::w[i] = w;
    }
    Dfs(1, 0);
    typedef std::pair<ll, int> pii;
    std::set<pii> s;
    ll now = 0;
    for (int i = 1; i <= n; ++i)
      s.insert(std::make_pair(1ll * w[i] * sze[i] - 1ll * (w[i] >> 1) * sze[i], i)), now += 1ll * w[i] * sze[i];
    int ans = 0;
    while (now > m) {
      auto qwq = s.rbegin()->second;
      s.erase(std::prev(s.end()));
      auto qaq = 1ll * w[qwq] * sze[qwq] - 1ll * (w[qwq] >> 1) * sze[qwq];
      w[qwq] >>= 1;
      now -= qaq;
      qaq = 1ll * w[qwq] * sze[qwq] - 1ll * (w[qwq] >> 1) * sze[qwq];
      s.insert(std::make_pair(qaq, qwq));
      ++ans;
    }
    printf("%d\n", ans);
    for (int i = 1; i <= n; ++i)
      head[i] = sze[i] = 0;
    edge_cnt = 0;
  }
}
