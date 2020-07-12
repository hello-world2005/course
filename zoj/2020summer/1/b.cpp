#include <cstdio>

const int N = 1e5 + 10;

double a[N], ans[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, k;
    double sum = 0;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
      scanf("%lf", &a[i]), sum += a[i];
    for (int i = 1; i <= n; ++i)
      ans[i] = a[i] + 1.0 * a[i] / sum * k;
    for (int i = 1; i <= n; ++i)
      printf("%.6f ", ans[i]);
    printf("\n");
  }
  return 0;
}
