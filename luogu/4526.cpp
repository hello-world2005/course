#include <cmath>
#include <cstdio>

const double EPS = 1e-8;

double a;

double F(double x) {
  return pow(x, a / x - x);
}

double Simpson(double l, double r) {
  return (r - l) * (F(l) + 4 * F((l + r) / 2) + F(r)) / 6;
}

double Solve(double l, double r, double pre, double EPS) {
  double mid = (l + r) / 2;
  double x = Simpson(l, mid), y = Simpson(mid, r);
  if (fabs(x + y - pre) < EPS * 15)
    return x + y + (x + y - pre) / 15;
  return Solve(l, mid, x, EPS / 2) + Solve(mid, r, y, EPS / 2);
}

int main() {
  scanf("%lf", &a);
  if (a < 0)
    return printf("orz\n"), 0;
  printf("%.5lf\n", Solve(EPS, 20, Simpson(0, 20), EPS));
  return 0;
}
