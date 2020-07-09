#include <cmath>
#include <cstdio>

const double EPS = 1e-8;

double a, b, c, d;

double F(double x) {
  return (c * x + d) / (a * x + b);
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
  double l, r;
  scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &l, &r);
  printf("%.6lf\n", Solve(l, r, Simpson(l, r), EPS));
  return 0;
}
