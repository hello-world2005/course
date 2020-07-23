#include <algorithm>
#include <cmath>
#include <cstdio>

const double PI = acos(-1.0);
double x[2], y[2], z[2];
double R, r;
double d;

int main() {
  scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &x[0], &y[0], &z[0], &R, &x[1], &y[1],
        &z[1], &r);
  double d =
      sqrt((x[0] - x[1]) * (x[0] - x[1]) + (y[0] - y[1]) * (y[0] - y[1]) +
           (z[0] - z[1]) * (z[0] - z[1]));
  double v1 = 4 * PI * R * R * R / 3, v2 = 4 * PI * r * r * r / 3;
  if (d >= R + r) {
    printf("%.7lf\n", v1 + v2);
  }
  else if (fabs(R - r) >= d) {
    printf("%.7lf\n", std::max(v1, v2));
  }
  else {
    if (R < r)
      std::swap(R, r);
    double insrt =
        (PI * (R + r - d) * (R + r - d) *
         (d * d + 2 * d * r - 3 * r * r + 2 * d * R + 6 * r * R - 3 * R * R)) /
        (12 * d);
    printf("%.7lf\n", v1 + v2 - insrt);
  }
  return 0;
}