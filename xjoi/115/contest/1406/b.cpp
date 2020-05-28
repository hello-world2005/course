#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;

#define pb push_back
#define sz(a) (int(a.size()))

const int N = 500;
const int inf = 0x7f7f7f7f;

// programed by Wendigo
const int T = (N << 1) + 2;
int s, t, fn, flow, cost, dep[T + 7], vis[T + 7], qc, q[T + 7];
vector<int> e[T + 7], to, fw, co;
void add(int u, int v, int f, int c) {
  // printf("%d %d %d %d\n",u,v,f,c);
  e[u].pb(sz(to)), to.pb(v), fw.pb(f), co.pb(+c);
  e[v].pb(sz(to)), to.pb(u), fw.pb(0), co.pb(-c);
}
int Bfs() {
  fill(vis + 1, vis + fn + 1, 0), fill(dep + 1, dep + fn + 1, inf);
  q[qc = 0] = t, vis[t] = 1, dep[t] = 0;
  for (int i = 0; i != (qc + 1) % T; i = (i + 1) % T) {
    int u = q[i];
    vis[u] = 0;
    for (int v : e[u])
      if (fw[v ^ 1] && dep[to[v]] > dep[u] - co[v]) {
        dep[to[v]] = dep[u] - co[v];
        if (!vis[to[v]])
          vis[to[v]] = 1, q[qc = (qc + 1) % T] = to[v];
      }
  }
  return dep[s] < inf;
}
int Dfs(int u, int fs) {
  vis[u] = 1;
  if (u == t || !fs)
    return fs;
  int f, fl = 0;
  for (int v : e[u])
    if (!vis[to[v]] && fw[v] && dep[u] - co[v] == dep[to[v]] &&
        (f = Dfs(to[v], min(fs, fw[v]))) > 0) {
      cost += co[v] * f, fw[v] -= f, fw[v ^ 1] += f, fs -= f, fl += f;
      if (!fs)
        break;
    }
  return fl;
}
void Mcmf() {
  while (Bfs())
    for (vis[t] = 1; vis[t];)
      fill(vis + 1, vis + fn + 1, 0), flow += Dfs(s, inf);
}

int a[N + 7][N + 7];

signed main() {
  int n1, n2, m;
  scanf("%d%d%d", &n1, &n2, &m);
  s = n1 + n2 + 1, t = n1 + n2 + 2;
  fn = n1 + n2 + 2;
  for (int i = 1; i <= n1; ++i)
    add(s, i, 1, 0);
  for (int i = n1 + 1; i <= n1 + n2; ++i)
    add(i, t, 1, 0);
  for (int i = 1, u, v; i <= m; ++i) {
    int w;
    scanf("%d%d%d", &u, &v, &w);
    a[u][v] = std::max(a[u][v], w);
    // printf("%lld %lld %lld\n", u, v + n1, w);
    // printf("qwq\n");
  }
  for (int u = 1; u <= n1; ++u)
    for (int v = 1; v <= n2; ++v)
      if (a[u][v])
        add(u, v + n1, 1, -a[u][v]);
  Mcmf();
  printf("%d\n", -cost);
  return 0;
}
