#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 510;
const int M = 125010;

int deg[N];
double f[M], g[N], x[N];
double a[N][N];

void Gauss(int n) {
  for (int i = 1; i <= n; ++i) {
    int p = i;
    for (int j = i + 1; j <= n; ++j)
      if (fabs(a[p][i]) < fabs(a[j][i]))
        p = j;
    if (i != p)
      std::swap(a[p], a[i]), std::swap(f[p], f[i]);
    for (int j = i + 1; j <= n; ++j) {
      double x = a[j][i] / a[i][i];
      f[j] -= x * f[i];
      for (int k = i; k <= n; ++k)
        a[j][k] -= x * a[i][k];
    }
  }
  for (int i = n; i >= 1; --i) {
    for (int j = i + 1; j <= n; ++j)
      f[i] -= x[j] * a[i][j];
    x[i] = f[i] / a[i][i];
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  typedef std::pair<int, int> Edge;
  std::vector<Edge> e(m + 1);
  for (int i = 1; i <= m; ++i)
    scanf("%d%d", &e[i].first, &e[i].second), ++deg[e[i].first], ++deg[e[i].second];
  for (int i = 1; i < n; ++i)
    a[i][i] = 1;
  for (int i = 1; i <= m; ++i) {
    int u = e[i].first, v = e[i].second;
    if (u != n && v != n)
      a[u][v] = -1.0 / deg[v],
      a[v][u] = -1.0 / deg[u];
  }
  f[1] = 1;
  Gauss(n - 1);
  memset(f, 0, sizeof(f));
  for (int i = 1; i <= m; ++i) {
    int u = e[i].first, v = e[i].second;
    if (u != n)
      f[i] += x[u] / deg[u];
    if (v != n)
      f[i] += x[v] / deg[v];
  }
  std::sort(f + 1, f + m + 1);
  std::reverse(f + 1, f + m + 1);
  double ans = 0;
  for (int i = 1; i <= m; ++i)
    ans += f[i] * i;
  printf("%.3lf\n", ans);
  return 0;
}
