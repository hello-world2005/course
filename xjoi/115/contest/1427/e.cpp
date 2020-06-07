// #include <cstdio>
// #include <cstring>
// #include <queue>

// typedef long long ll;

// const int N = 5e4 + 10;
// const int M = 2e5 + 10;

// int n, m;
// struct Edge {
//   int v;
//   ll w;
//   int nxt;
//   bool re;

//   Edge() : v(0), w(0), nxt(0), re(false) {}
//   Edge(int _v, ll _w, int _nxt, bool _re) : v(_v), w(_w), nxt(_nxt), re(_re) {}
// } e[M << 1];
// int head[N], edge_cnt;

// void AddEdge(int u, int v, ll w, bool re) {
//   e[++edge_cnt] = Edge(v, w, head[u], re);
//   head[u] = edge_cnt;
// }

// int a, b, c, d;

// ll dis[5][N];
// bool in_que[N];
// std::priority_queue<std::pair<ll, int> > q;

// void Dijkstra(int s, int opt) {
//   memset(in_que, false, sizeof(in_que));
//   dis[opt][s] = 0;
//   q.push(std::make_pair(0, s));
//   while (!q.empty()) {
//     auto u = q.top();
//     q.pop();
//     if (in_que[u.second])
//       continue;
//     in_que[u.second] = true;
//     dis[opt][u.second] = -u.first;
//     for (int i = head[u.second]; i; i = e[i].nxt) {
//       int v = e[i].v;
//       ll w = e[i].w;
//       // printf("%d %d %d\n", u.second, v, e[i].re);
//       if (!((opt % 2) ^ e[i].re) && -u.first + w < dis[opt][v])
//         q.push(std::make_pair(u.first - w, v));
//     }
//   }
//   // for (int i = 1; i <= n; ++i)
//   //   printf("%lld ", dis[opt][i]);
//   // printf("\n");
// }

// int deg[N], dp[N];
// bool ok[M << 1];

// int main() {
//   scanf("%d%d", &n, &m);
//   for (int i = 1, u, v; i <= n; ++i) {
//     ll w;
//     scanf("%d%d%lld", &u, &v, &w);
//     AddEdge(u, v, w, true);
//     AddEdge(v, u, w, false);
//   }
//   scanf("%d%d%d%d", &a, &b, &c, &d);
//   memset(dis, 0x3f, sizeof(dis));
//   Dijkstra(a, 1), Dijkstra(b, 2), Dijkstra(c, 3), Dijkstra(d, 4);
//   if (dis[1][b] == dis[0][0] || dis[3][d] == dis[0][0]) {
//     printf("-1\n");
//     return 0;
//   }
//   // for (int i = 1; i <= 4; ++i) {
//   //   for (int u = 1; u <= n; ++u)
//   //     printf("%lld ", dis[i][u]);
//   //   printf("\n");
//   // }
//   for (int u = 1; u <= n; ++u)
//     for (int i = head[u]; i; i = e[i].nxt) {
//       // printf("%d %d %d\n", u, e[i].v, e[i].re);
//       if (e[i].re && dis[1][u] + e[i].w + dis[2][e[i].v] == dis[1][b] &&
//           dis[3][u] + e[i].w + dis[4][e[i].v] == dis[3][d])
//         ++deg[e[i].v], ok[i] = true;
//     }
//   std::queue<int> q;
//   memset(in_que, false, sizeof(in_que));
//   for (int i = 1; i <= n; ++i)
//     if (!deg[i])
//       q.push(i), dp[i] = 1, in_que[i] = true;
//   int ans = 0;
//   while (!q.empty()) {
//     int u = q.front();
//     q.pop();
//     in_que[u] = false;
//     for (int i = head[u]; i; i = e[i].nxt)
//       if (ok[i]) {
//         int v = e[i].v;
//         dp[v] = std::max(dp[v], dp[u] + 1);
//         ans = std::max(ans, dp[v]);
//         --deg[v];
//         if (deg[v] <= 0 && !in_que[v])
//           q.push(v), in_que[v] = true;
//       }
//   }
//   printf("%d\n", ans);
//   return 0;
// }

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 50005;
const int maxm = 200005;
struct node {
  int id;
  long long d;
};
bool operator<(node a, node b) {
  return a.d > b.d;
}
int info[maxn], nx[maxm << 1], v[maxm << 1], w[maxm << 1], re[maxm << 1];
long long d[5][maxn];
int n, m, en, ans, ecnt, p[5], dp[maxn], vis[maxn], inp[maxn], top[maxn],
    lef[maxm << 1];
priority_queue<node> q;
void add(int u1, int v1, int w1, int r) {
  nx[++ecnt] = info[u1];
  info[u1] = ecnt;
  v[ecnt] = v1;
  w[ecnt] = w1;
  re[ecnt] = r;
}
void SPFA(int k) {
  memset(vis, 0, sizeof vis);
  d[k][p[k]] = 0;
  q.push((node){p[k], 0});
  while (!q.empty()) {
    node nw = q.top();
    q.pop();
    if (vis[nw.id] == 1)
      continue;
    vis[nw.id] = 1;
    d[k][nw.id] = nw.d;
    for (int i = info[nw.id]; i; i = nx[i]) {
      // printf("%d %d\n", v[i], re[i]);
      if (!((k % 2) ^ re[i]) && d[k][v[i]] > nw.d + w[i])
        q.push((node){v[i], nw.d + w[i]});
    }
  }
  // for (int i = 1; i <= n; ++i)
  //   printf("%lld ", d[k][i]);
  // printf("\n");
}
int main() {
  scanf("%d%d", &n, &m);
  memset(d, 0x7f, sizeof d);
  for (int i = 1, u1, v1, w1; i <= m; i++)
    scanf("%d%d%d", &u1, &v1, &w1), add(u1, v1, w1, 1), add(v1, u1, w1, 0);
  for (int k = 1; k <= 4; k++)
    scanf("%d", &p[k]), SPFA(k);
  if (d[1][p[2]] == d[0][0] || d[3][p[4]] == d[0][0]) {
    puts("-1");
    return 0;
  }
  for (int x = 1; x <= n; x++) {
    for (int e = info[x]; e; e = nx[e])
      if (re[e] && d[1][x] + w[e] + d[2][v[e]] == d[1][p[2]] &&
          d[3][x] + w[e] + d[4][v[e]] == d[3][p[4]])
        lef[e] = 1, inp[v[e]]++;
  }
  for (int x = 1; x <= n; x++)
    if (inp[x] == 0)
      top[++en] = x, dp[x] = 1;
  for (int i = 1; i <= en; i++) {
    int nw = top[i];
    for (int e = info[nw]; e; e = nx[e])
      if (lef[e]) {
        dp[v[e]] = max(dp[v[e]], dp[nw] + 1);
        ans = max(ans, dp[v[e]]);
        inp[v[e]]--;
        if (!inp[v[e]])
          top[++en] = v[e];
      }
  }
  printf("%d\n", ans);
}

// 记得改
