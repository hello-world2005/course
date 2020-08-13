#include <cstdio>

const int N = 210;

int a[N], b[N];
int f[N][N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  for (int i = 1; i <= m; ++i)
    scanf("%d", &b[i]);
  int ans = 0;
  // for (int i = 10; i >= 0; --i) {
  //   bool flag = true;
  //   for (int j = 1; j <= n; ++j) {
  //     bool qwq = false;
  //     for (int k = 1; k <= m; ++k)
  //       if (f[j][k] && (a[j] >> i & 1) && (b[k] >> i & 1))
  //         qwq = true;
  //     flag &= qwq;
  //   }
  //   if (flag)
  //     ans += (1 << i);
  //   for (int j = 1; j <= n; ++j)
  //     for (int k = 1; k <= m; ++k)
  //       f[j][k] |= ((a[j] >> i & 1) && (b[k] >> i & 1));
  // }
  for (int i = 0; i < (1 << 9); ++i) {
    bool flag = true;
    for (int j = 1; j <= n; ++j) {
      bool qwq = false;
      for (int k = 1; k <= m; ++k)
        if (((a[j] & b[k]) | i) == i) {
          qwq = true;
          break;
        }
      flag &= qwq;
    }
    if (flag)
      return printf("%d\n", i), 0;
  }
  printf("%d\n", ans);
  return 0;
}
