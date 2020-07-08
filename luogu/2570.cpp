#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <queue>

const int N = 2000;
const int M = 100000;
const double EPS = 1e-5;
const int INF = 0x3f3f3f3f;

int n, m;
double p[N], st[N], en[N];  // p_i r_i d_i
double a[N];
double sum_p;

struct Edge {
  int v;
  double w;
  int nxt;

  Edge() : v(0), w(0), nxt(0) {}
  Edge(int _v, double _w, int _nxt) : v(_v), w(_w), nxt(_nxt) {}
} e[M << 1];
int head[N], edge_cnt;

void AddEdge(int u, int v, double w) {
  e[++edge_cnt] = Edge(v, w, head[u]);
  head[u] = edge_cnt;
}

int dep[N];
int cur[N];

bool Bfs(int s, int t) {
  for (int i = 0; i <= 2 * n * m + n + 1; ++i)
    cur[i] = head[i], dep[i] = 0;
  std::queue<int> q;
  dep[s] = 1;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v;
      double w = e[i].w;
      if (w < EPS || dep[v])
        continue;
      dep[v] = dep[u] + 1;
      q.push(v);
    }
  }
  return dep[t] > 0;
}

// double Dfs(int u, double val, int t) {
//   if (u == t)
//     return val;
//   double res = 0;
//   // printf("%d %d\n", u, head[u]);
//   for (int i = head[u]; i; i = e[i].nxt) {
//     int v = e[i].v;
//     double w = e[i].w;
//     if (w < EPS || dep[v] != dep[u] + 1)
//       continue;
//     double now = Dfs(v, std::min(val, w), t);
//     e[i].w -= now;
//     e[(i & 1) ? i + 1 : i - 1].w += now;
//     val -= now;
//     res += now;
//   }
//   if (res < EPS)
//     dep[u] = 0;
//   return res;
// }

double Dfs(int u, double val, int t) {
  if (u == t || val < EPS)
    return val;
  double res = 0, now;
  // printf("%d %d\n", u, cur[u]);
  for (int i = cur[u]; i; i = e[i].nxt) {
    cur[u] = i;
    int v = e[i].v;
    // printf("%d %d\n", u, v);
    double w = e[i].w;
    if (dep[v] != dep[u] + 1 || (now = Dfs(v, std::min(val, w), t)) < EPS)
      continue;
    e[i].w -= now;
    e[i ^ 1].w += now;
    val -= now;
    res += now;
    if (val < EPS)
      break;
  }
  return res;
}

double Dinic(int s, int t) {
  double res = 0;
  while (Bfs(s, t)) {
    res += Dfs(s, INF, t);
    // printf("%.4f\n", res);
  }
  return res;
}

double ti[N << 1];

void Build(int s, int t, double mid) {
  memset(head, 0, sizeof(head));
  edge_cnt = 1;
  for (int i = 1; i <= n; ++i) {
    AddEdge(s, i, p[i]);
    AddEdge(i, s, 0);
  }
  for (int i = 1; i <= n; ++i) {
    ti[2 * i - 1] = st[i];
    ti[2 * i] = en[i] + mid;
  }
  std::sort(ti + 1, ti + 2 * n + 1);
  int cnt = n;
  for (int i = 1; i <= m; ++i) {
    double now = ti[1];
    for (int j = 2; j <= 2 * n; ++j) {
      if (ti[j] - now < EPS)
        continue;
      AddEdge(++cnt, t, i * a[i] * (ti[j] - now));
      AddEdge(t, cnt, 0);
      for (int k = 1; k <= n; ++k)
        if (st[k] - now < EPS && en[k] + mid - ti[j] > -EPS) {
          AddEdge(k, cnt, a[i] * (ti[j] - now));
          AddEdge(cnt, k, 0);
        }
      now = ti[j];
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    sum_p = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
      scanf("%lf%lf%lf", &p[i], &st[i], &en[i]), sum_p += p[i];
    for (int i = 1; i <= m; ++i)
      scanf("%lf", &a[i]);
    std::sort(a + 1, a + m + 1, std::greater<double>());
    double l = 0, r = sum_p / a[1] + 1;
    for (int i = 1; i < m; ++i)
      a[i] -= a[i + 1];
    // printf("%.4f %.4f\n", l, r);
    int s = 0, t = n * m * 2 + n + 1;
    while (fabs(l - r) > EPS) {
      double mid = (l + r) / 2;
      Build(s, t, mid);
      // printf("%f %f %f\n", l, r, mid);
      double res = Dinic(s, t);
      // printf("Solve(%.4f): %.4f\n", mid, res);
      if (sum_p - res < EPS)
        r = mid;
      else
        l = mid;
    }
    printf("%.4f\n", l);
  }
  return 0;
}
