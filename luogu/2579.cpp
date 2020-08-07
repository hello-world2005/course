#include <cstdio>
#include <cstring>

const int N = 60;
const int MOD = 1e4;

struct Matrix {
  int n;
  int a[N][N];

  Matrix() : n(0) { memset(a, 0, sizeof(a)); }
  Matrix(int _n) : n(_n) { memset(a, 0, sizeof(a)); }
  Matrix(int _n, int _x) : n(_n) {
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= n; ++i)
      a[i][i] = _x;
  }

  Matrix operator*(const Matrix& rhs) {
    Matrix res(n);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        for (int k = 1; k <= n; ++k)
          res.a[i][j] = (res.a[i][j] + a[i][k] * rhs.a[k][j]) % MOD;
    return res;
  }
};

int n, m, s, t, k, o;
int map[N][N], cro[N][N];

Matrix FastPow(Matrix a, int b) {
  Matrix res(a.n, 1);
  for (; b; b >>= 1, a = a * a)
    if (b & 1)
      res = res * a;
  // printf("==========\n");
  // for (int i = 1; i <= n; ++i) {
  //   for (int j = 1; j <= n; ++j)
  //     printf("%d ", res.a[i][j]);
  //   printf("\n");
  // }
  // printf("==========\n");
  return res;
}

int main() {
  scanf("%d%d%d%d%d", &n, &m, &s, &t, &k);
  ++s, ++t;
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d%d", &u, &v);
    ++u, ++v;
    map[u][v] = map[v][u] = 1;
  }
  scanf("%d", &o);
  for (int i = 1, x; i <= o; ++i) {
    scanf("%d", &x);
    for (int j = 0, u; j < x; ++j) {
      scanf("%d", &u);
      ++u;
      for (int k = j; k < 12; k += x)
        cro[k][u] = 1;
    }
  }
  Matrix qwq(n);
  for (int i = 1; i <= n; ++i)
    qwq.a[i][i] = 1;
  Matrix qaq[12];
  for (int x = 0; x < 12; ++x) {
    qaq[x] = Matrix(n);
    for (int i = 1; i <= qwq.n; ++i)
      for (int j = 1; j <= qwq.n; ++j)
        qaq[x].a[i][j] = (map[i][j] && !cro[x][j]);
  }
  for (int i = 1; i <= 12; ++i)
    qwq = qwq * qaq[i % 12];
  Matrix res(n);
  for (int i = 1; i <= n; ++i)
    res.a[i][i] = 1;
  res = res * FastPow(qwq, k / 12);
  // printf("==========\n");
  // for (int x = 1; x <= n; ++x) {
  //   for (int y = 1; y <= n; ++y)
  //     printf("%d ", res.a[x][y]);
  //   printf("\n");
  // }
  // printf("==========\n");
  for (int i = 1; i <= k % 12; ++i)
    res = res * qaq[i];
  printf("%d\n", res.a[s][t]);
  return 0;
}
