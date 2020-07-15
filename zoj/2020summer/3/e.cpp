#include <algorithm>
#include <cmath>
#include <cstdio>

const int N = 1e6 + 10;

double a[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    double n, m, x;
    scanf("%lf%lf%lf", &n, &m, &x);
    a[0] = m;
    double ans;
    for (int i = 1; i <= 2 * n; ++i)
      a[i] = m * a[i - 1] * (1 - a[i - 1]);
    printf("%.10lf\n", ans);
  }
  return 0;
}
