#include <cstdio>
#include <cstring>

#define int long long

typedef long long ll;

const int N = 1e5 + 10;
const int M = 2e5 + 10;
const int K = 64;
const int MOD = 1e9 + 7;

int n, m;
struct Edge {
  int v, nxt;
  ll w;

  Edge() : v(0), w(0ll), nxt(0) {}
  Edge(int _v, ll _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[M << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v, ll w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

ll d[K];

bool Insert(ll k) {
  for (int i = 59; i >= 0; --i)
    if (k >> i & 1ll) {
      if (!d[i]) {
        d[i] = k;
        return true;
      } else {
        k ^= d[i];
      }
    }
  return false;
}

bool vis[N];
ll p[N];
int s[N], po, tp;

void Dfs(int u, ll sum) {
  // printf("%lld %lld %lld %lld\n", u, sum, po, tp);
  vis[u] = true;
  p[u] = sum;
  s[++tp] = u;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    ll w = e[i].w;
    if (!vis[v])
      Dfs(v, sum ^ w);
    else
      po += Insert(sum ^ p[v] ^ w);
  }
}

signed main() {
  scanf("%lld%lld", &n, &m);
  for (int i = 1, u, v; i <= m; ++i) {
    ll w;
    scanf("%lld%lld%lld", &u, &v, &w);
    AddEdge(u, v, w);
    AddEdge(v, u, w);
  }
  ll ans = 0;
  for (int i = 1; i <= n; ++i)
    if (!vis[i]) {
      memset(d, 0, sizeof(d));
      po = 0, tp = 0;
      Dfs(i, 0);
      for (int j = 0; j < 60; ++j) {
        ll c = (1ll << j) % MOD;
        bool flag = 0;
        for (int k = 0; k < 60; ++k)
          if (d[k] >> j & 1)
            flag = 1;
        if (flag) {
          ans = (ans + (ll)tp * (tp - 1) / 2 % MOD * ((1ll << po - 1) % MOD) %
                           MOD * c) %
                MOD;
          // printf("%lld\n", tp * (tp - 1) / 2 * ((1ll << po - 1)) * c);
        } else {
          int x = 0;
          for (int i = 1; i <= tp; ++i)
            if (p[s[i]] >> j & 1)
              ++x;
          ans = (ans + (ll)x * (tp - x) % MOD * ((1ll << po) % MOD) % MOD * c) %
                MOD;
          // printf("%lld\n", x);
        }
      }
    }
  printf("%lld\n", ans);
  return 0;
}
