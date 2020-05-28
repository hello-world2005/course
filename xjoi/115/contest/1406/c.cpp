#include <algorithm>
#include <cmath>
#include <cstdio>

const int N = 6e4 + 10;
const double EPS = 1e-6;

int n;
int a[N], b[N];

double Check(double x) {
  double res = 0;
  for (int i = 1; i <= n; ++i)
    res = std::max(res, 1.0 * fabs(a[i] - x) / b[i]);
  return res;
}

int main() {
  scanf("%d", &n);
  int maxa = 0;
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), maxa = std::max(maxa, a[i]);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &b[i]);
  double l = 0, r = maxa;
  while (fabs(l - r) >= EPS) {
    // printf("%.6f %.6f\n", l, r);
    double mid = (l + r) / 2;
    if (Check(mid + EPS) < Check(mid - EPS))
      l = mid;
    else
      r = mid;
  }
  printf("%.5f", Check(l));
  return 0;
}