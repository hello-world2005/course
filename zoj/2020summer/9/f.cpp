#include <algorithm>
#include <cstdio>

const int N = 110;
const int M = N * N;
const int MOD = 998244353;

int f[N][N];
int fac[M], inv[M];

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % MOD)
    if (b & 1)
      res = 1ll * res * a % MOD;
  return res;
}

void Init() {
  fac[0] = inv[0] = 1;
  for (int i = 1; i < M; ++i) {
    fac[i] = 1ll * fac[i - 1] * i % MOD;
    inv[i] = FastPow(fac[i], MOD - 2);
  }
}

inline int C(int n, int m) {
  if (m > n)
    return 0;
  return 1ll * fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int main() {
  Init();
  int n;
  scanf("%d", &n);
  f[1][0] = 1;
  for (int i = 2; i <= n; ++i) {
    // printf("i: %d\n", i);
    for (int j = i - 1; j <= i * (i - 1) / 2; ++j) {
      f[i][j] = C(i * (i - 1) / 2, j);
      for (int a = 1; a <= i - 1; ++a)
        for (int b = a - 1; b <= std::min(a * (a - 1) / 2, j); ++b)
          f[i][j] = (f[i][j] -
                     1ll * f[a][b] * C((i - a) * (i - a - 1) / 2, j - b) % MOD *
                         C(i - 1, a - 1) % MOD +
                     MOD) %
                    MOD;
    }
  }
  // FILE *dat = fopen("f.out", "w");
  // for (int i = 1; i <= n; ++i) {
  //   fprintf(dat, "{");
  //   for (int j = 0; j < i * (i - 1) / 2; ++j)
  //     fprintf(dat, "%d,", f[i][j]);
  //   fprintf(dat, "%d}%c", f[i][i * (i - 1) / 2], i == n ? '\n' : ',');
  // }

  for (int i = 0; i <= n * (n - 1) / 2; ++i)
    printf("%d\n", (f[n][i] + MOD) % MOD);
  return 0;
}
