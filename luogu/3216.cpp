#include <cmath>
#include <cstdio>
#include <cstring>

#define int unsigned long long

typedef unsigned long long ll;

ll n, p;
#define MOD p

struct Matrix {
  int a[3][3];

  Matrix() { memset(a, 0, sizeof(a)); }
  Matrix(int _x) {
    memset(a, 0, sizeof(a));
    for (int i = 0; i <= 2; ++i)
      a[i][i] = 1;
  }

  Matrix operator*(const Matrix& rhs) {
    Matrix res;
    for (int i = 0; i <= 2; ++i)
      for (int j = 0; j <= 2; ++j)
        for (int k = 0; k <= 2; ++k)
          res.a[i][j] = (res.a[i][j] + 1ll * a[i][k] * rhs.a[k][j] % MOD) % MOD;
    return res;
  }
} qwq, ans(1);

Matrix FastPow(Matrix a, int b) {
  Matrix res(1);
  for (; b; b >>= 1, a = a * a)
    if (b & 1)
      res = res * a;
  return res;
}

void Solve(ll a, ll b) {
  qwq.a[0][0] = a % MOD;
  qwq.a[0][1] = qwq.a[0][2] = qwq.a[1][1] = qwq.a[1][2] = qwq.a[2][2] = 1;
  ans = FastPow(qwq, b) * ans;
}

signed main() {
  scanf("%lld%lld", &n, &p);
  ll r = 10;
  while (r <= n)
    Solve(r, r - (r / 10)), r *= 10;
  Solve(r, n - r / 10 + 1);
  printf("%lld\n", ans.a[0][2]);
  return 0;
}
