#include <cstdio>
#include <cstring>

#define int long long

const int N = 2e5 + 10;
const int M = 5e5 + 10;

struct Edge {
  int v, nxt;

  Edge() : v(0), nxt(0) {}
  Edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} e[M << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v) {
  e[++edge_cnt] = Edge(v, head[u]);
  head[u] = edge_cnt;
}

bool vis[N];

// int Dfs(int u, int fa) {
//   if (u == fa)
//     return 0;
//   int res = 1;
//   vis[u] = true;
//   bool ed = false;
//   for (int i = head[u]; i; i = e[i].nxt) {
//     int v = e[i].v;
//     if (v == fa)
//       ed = true;
//     if (vis[v])
//       continue;
//     int t = Dfs(v, fa);
//     if (t)
//       res += t;
//     else
//       ed = true;
//   }
//   if (ed)
//     return 0;
//   return res;
// }

bool vis1[N], vis2[N];

void Dfs1(int u, int fa) {
  vis1[u] = true;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa || vis1[v])
      continue;
    Dfs1(v, fa);
  }
}

void Dfs2(int u, int fa) {
  vis2[u] = true;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa || vis2[v])
      continue;
    Dfs2(v, fa);
  }
}

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int n, m, a, b;
    memset(head, 0, sizeof(head));
    edge_cnt = 0;
    scanf("%lld%lld%lld%lld", &n, &m, &a, &b);
    for (int i = 1, u, v; i <= m; ++i) {
      scanf("%lld%lld", &u, &v);
      AddEdge(u, v);
      AddEdge(v, u);
    }
    // memset(vis, false, sizeof(vis));
    // int ans1 = 0, ans2 = 0;
    // vis[a] = vis[b] = true;
    // for (int i = head[a]; i; i = e[i].nxt) {
    //   int v = e[i].v;
    //   if (!vis[v])
    //     ans1 = Dfs(v, b);
    // }
    // for (int i = head[b]; i; i = e[i].nxt) {
    //   int v = e[i].v;
    //   if (!vis[v])
    //     ans2 += Dfs(v, a);
    // }
    // printf("%lld %lld\n", ans1, ans2);
    int ans1 = 0, ans2 = 0;
    memset(vis1, false, sizeof(vis1));
    memset(vis2, false, sizeof(vis2));
    Dfs1(a, b);
    Dfs2(b, a);
    for (int i = 1; i <= n; ++i) {
      if (vis1[i] && !vis2[i] && i != a)
        ++ans1;
      if (vis2[i] && !vis1[i] && i != b)
        ++ans2;
    }
    printf("%lld\n", ans1 * ans2);
  }
  return 0;
}
