#include <cstdio>
#include <unordered_map>

typedef long long ll;

const int N = 2e5 + 10;

int n;
ll k;
struct Edge {
  int v;
  ll w;
  int nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, ll _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[N << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v, ll w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int sze[N], s[N];
ll dep[N];
int len[N];
int l[N], r[N], idx[N], ti_stamp;

void GetSze(int u, int fa) {
  sze[u] = 1;
  l[u] = ++ti_stamp;
  idx[ti_stamp] = u;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    ll w = e[i].w;
    if (v == fa)
      continue;
    dep[v] = dep[u] + w;
    len[v] = len[u] + 1;
    GetSze(v, u);
    sze[u] += sze[v];
    if (sze[s[u]] < sze[v])
      s[u] = v;
  }
  r[u] = ti_stamp;
}

int ans = 0x3f3f3f3f;
std::unordered_map<ll, int> d;
int cnt[N];

void Calc(int u, int w) {
  int now = dep[u];
  if (~w) {
    int minn = d[now] ? d[now] : 0x3f3f3f3f;
    d[now] = std::min(len[u], minn);
  } else {
    d[now] = 0;
  }
}

void Dfs(int u, int fa, bool flag) {
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa || v == s[u])
      continue;
    Dfs(v, u, false);
  }
  if (s[u])
    Dfs(s[u], u, true);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa || v == s[u])
      continue;
    for (int j = l[v]; j <= r[v]; ++j) {
      int vv = idx[j];
      int require = k + 2 * dep[u] - dep[vv];
      if (d[require])
        ans = std::min(ans, d[require] + len[vv] - 2 * len[u]);
    }
    for (int j = l[v]; j <= r[v]; ++j)
      Calc(idx[j], 1);
  }
  Calc(u, 1);
  if (d[dep[u] + k])
    ans = std::min(ans, d[dep[u] + k] - len[u]);
  if (!flag)
    for (int i = l[u]; i <= r[u]; ++i)
      Calc(idx[i], -1);
}

int main() {
  scanf("%d%lld", &n, &k);
  for (int i = 2, u, v; i <= n; ++i) {
    ll w;
    scanf("%d%d%lld", &u, &v, &w);
    ++u, ++v;
    AddEdge(u, v, w);
    AddEdge(v, u, w);
  }
  len[1] = 1;
  GetSze(1, 0);
  Dfs(1, 0, false);
  printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
  return 0;
}
