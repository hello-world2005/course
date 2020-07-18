#include <cmath>
#include <cstdio>
#include <ctime>
#include <random>

const int N = 1e6 + 10;
const double EPS = 1e-10;

double a[N];
std::mt19937 rnd(time(NULL));

bool Eq(double lhs, double rhs) {
  return fabs(lhs - rhs) < EPS;
}

double F(int n, double m, double x0) {
  for (int i = 1; i <= n; ++i)
    x0 = m * x0 * (1 - x0);
  return x0;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    double m, x;
    scanf("%d%lf%lf", &n, &m, &x);
    if (Eq(x, 0)) {
      printf("0\n");
      continue;
    }
    while (true) {
      double x0 = (rnd() % (int)1e7) / 1e7;
      if (Eq(F(n, m, x0), x)) {
        printf("%.8lf\n", x0);
        break;
      }
    }
  }
  return 0;
}
