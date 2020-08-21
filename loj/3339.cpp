#include <algorithm>
#include <cstdio>
#include <cstring>

#define int long long

const int N = 260;

int e[N][N];

struct Matrix {
  int n, m, a[N][N];

  Matrix() { memset(a, 0xc0, sizeof(a)); }

  Matrix operator*(const Matrix& rhs) {
    Matrix res;
    res.n = n, res.m = rhs.m;
    // printf("%lld %lld\n", n, rhs.m);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= rhs.m; ++j)
        for (int k = 1; k <= m; ++k)
          res.a[i][j] = std::max(res.a[i][j], a[i][k] + rhs.a[k][j]);
    return res;
  }

  void Print() {
    printf("==========\n");
    printf("size: %dx%lld\n", n, m);
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j)
        printf("%lld ", a[i][j]);
      printf("\n");
    }
    printf("==========\n\n");
  }
};

int c[N];

void AddEdge(int u, int v, int w) {
  e[5 * (u - 1) + w][5 * (v - 1) + 1] = c[v];
}

struct Holiday {
  int t, x, y;

  Holiday()
      : t(0), x(0), y(0) {}

  bool operator<(const Holiday& rhs) const { return t < rhs.t; }
} hol[N];

Matrix f[N];

signed main() {
#ifndef DEBUG
  freopen("delicacy.in", "r", stdin);
  freopen("delicacy.out", "w", stdout);
#endif
  int n, m, t, k;
  scanf("%lld%lld%lld%lld", &n, &m, &t, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &c[i]);
  memset(e, 0xc0, sizeof(e));
  for (int i = 1, u, v, w; i <= m; ++i)
    scanf("%lld%lld%lld", &u, &v, &w), AddEdge(u, v, w);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j < 5; ++j)
      e[5 * (i - 1) + j][5 * (i - 1) + j + 1] = 0;
  Matrix initial, now;
  initial.n = initial.m = n * 5;
  for (int i = 0; i <= 5 * n; ++i)
    for (int j = 0; j <= 5 * n; ++j)
      initial.a[i][j] = e[i][j];
  f[0] = initial;
  for (int i = 1; i < 30; ++i)
    f[i] = f[i - 1] * f[i - 1];
  for (int i = 1; i <= k; ++i)
    scanf("%lld%lld%lld", &hol[i].t, &hol[i].x, &hol[i].y);
  std::sort(hol + 1, hol + k + 1);
  now.n = 1, now.m = n * 5;
  now.a[1][1] = c[1];
  for (int i = 1; i <= k; ++i) {
    for (int j = 0; j < 30; ++j)
      if ((hol[i].t - hol[i - 1].t) >> j & 1)
        now = now * f[j];
    now.a[1][(hol[i].x - 1) * 5 + 1] += hol[i].y;
  }
  // f[0].Print();
  for (int i = 0; i < 30; ++i)
    if ((t - hol[k].t) >> i & 1)
      now = now * f[i];
  int ans = now.a[1][1];
  if (ans < 0)
    printf("-1\n");
  else
    printf("%lld\n", ans);
  return 0;
}

// 11 = 1 + 2 + 8
