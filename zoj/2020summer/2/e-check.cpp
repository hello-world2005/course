#include <cstdio>

double FastPow(double a, int b) {
  double res = 0;
  for (; b; b >>= 1, a = a * a)
    if (b & 1)
      res = res * a;
  return res;
}

int main() {
  double a, b, c;
  scanf("%lf%lf%lf", &a, &b, &c);
  for (int i = 1; i <= a; ++i)
    c = b * c * (1 - c);
  printf("%.8lf\n", c);
  return 0;
}
