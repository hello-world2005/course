#include <cstdio>
#include <cstring>

double Fac(int x) {
  double res = 1;
  for (int i = 2; i <= x; ++i)
    res *= i;
  return res;
}

int main() {
  int n, m;
  int a[20];
  while (scanf("%d%d", &n, &m) == 2) {
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    double x[1000], y[1000];
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    for (int i = 0; i <= a[1]; ++i)
      x[i] = 1 / Fac(i);
    for (int i = 2; i <= n; ++i) {
      for (int j = 0; j <= m; ++j)
        for (int k = 0; k <= a[i] && j + k <= m; ++k)
          y[j + k] += x[j] / Fac(k);
      for (int j = 0; j <= m; ++j)
        x[j] = y[j], y[j] = 0;
    }
    printf("%.0lf\n", x[m] * Fac(m));
  }
  return 0;
}
