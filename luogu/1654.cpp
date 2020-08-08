#include <cstdio>

const int N = 1e5 + 10;

double a[N], dp[N];

double QwQ(double x) { return x * x * x; }

int main() {
  int n;
  scanf("%d", &n);
  double m1 = 0, m2 = 0;
  for (int i = 1; i <= n; ++i)
    scanf("%lf", &a[i]);
  for (int i = 1; i <= n; ++i)
    dp[i] = dp[i - 1] + a[i] * (3 * (m1 + m2) + 1), m2 = a[i] * (m2 + 2 * m1 + 1), m1 = a[i] * (m1 + 1);
  printf("%.1lf\n", dp[n]);
  return 0;
}
