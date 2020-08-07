#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>

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

int w[N], c[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    typedef long long ll;
    typedef std::pair<ll, int> pii;
    ll m;
    scanf("%d%lld", &n, &m);
    for (int i = 2, u, v, w; i <= n; ++i) {
      scanf("%d%d%d%d", &u, &v, &w, &c[i]);
      AddEdge(u, v, w, i), AddEdge(v, u, w, i);
      ::w[i] = w;
    }
    Dfs(1, 0);
    std::set<pii> s;
    ll now = 0;
    std::vector<ll> v1, v2;

    for (int i = 1; i <= n; ++i)
      if (c[i] == 1)
        s.insert(std::make_pair(1ll * w[i] * sze[i] - 1ll * (w[i] >> 1) * sze[i], i)), now += 1ll * w[i] * sze[i];
    v1.push_back(now);
    while (now > 0) {
      auto qwq = s.rbegin()->second;
      s.erase(std::prev(s.end()));
      auto qaq = 1ll * w[qwq] * sze[qwq] - 1ll * (w[qwq] >> 1) * sze[qwq];
      w[qwq] >>= 1;
      now -= qaq;
      v1.push_back(now);
      qaq = 1ll * w[qwq] * sze[qwq] - 1ll * (w[qwq] >> 1) * sze[qwq];
      s.insert(std::make_pair(qaq, qwq));
    }

    now = 0;
    for (int i = 1; i <= n; ++i)
      if (c[i] == 2)
        s.insert(std::make_pair(1ll * w[i] * sze[i] - 1ll * (w[i] >> 1) * sze[i], i)), now += 1ll * w[i] * sze[i];
    v2.push_back(now);
    while (now > 0) {
      auto qwq = s.rbegin()->second;
      s.erase(std::prev(s.end()));
      auto qaq = 1ll * w[qwq] * sze[qwq] - 1ll * (w[qwq] >> 1) * sze[qwq];
      w[qwq] >>= 1;
      now -= qaq;
      v2.push_back(now);
      qaq = 1ll * w[qwq] * sze[qwq] - 1ll * (w[qwq] >> 1) * sze[qwq];
      s.insert(std::make_pair(qaq, qwq));
    }

    int ans = 0x3f3f3f3f;
    for (int i = 0, j = (int)v2.size() - 1; i < (int)v1.size(); ++i) {
      while (j > 0 && v1[i] + v2[j - 1] <= m)
        --j;
      if (v1[i] + v2[j] <= m)
        ans = std::min(ans, i + 2 * j);
    }
    printf("%d\n", ans);

    for (int i = 1; i <= n; ++i)
      head[i] = sze[i] = 0;
    edge_cnt = 0;
  }
}
