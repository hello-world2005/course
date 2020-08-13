#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);
  double ans = 6.0 * (n - 1);
  for (int i = 1; i < n; ++i)
    ans -= 4.0 / i;
  printf("%.6lf\n", ans);
  return 0;
}
