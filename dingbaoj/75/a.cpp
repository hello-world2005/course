#include <algorithm>
#include <cstdio>

const int N = 17;
const int MOD = 998244353;

int n, m;
int a[N][N];
int g[1 << N], f[1 << N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      scanf("%d", &a[i][j]);
  g[0] = 1;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      for (int k = 0; k < (1 << m); ++k)
        f[k & (((1 << m) - 1) ^ (1 << j))] =
            (f[k & (((1 << m) - 1) ^ (1 << j))] + g[k]) % MOD;
      if (a[i][j])
        for (int k = 0; k < (1 << m); ++k) {
          if ((k >> j & 1) || (j && (k >> (j - 1) & 1)))
            continue;
          f[k | (1 << j)] = (f[k | (1 << j)] + g[k]) % MOD;
        }
      for (int k = 0; k < (1 << m); ++k)
        g[k] = f[k], f[k] = 0;
    }
  int ans = 0;
  for (int i = 0; i < (1 << m); ++i)
    ans = (ans + g[i]) % MOD;
  printf("%d\n", ans);
  return 0;
}
