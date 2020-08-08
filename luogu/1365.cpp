#include <cstdio>

const int N = 3e5 + 10;

char s[N];
double dp[N];

int main() {
  int n;
  double m = 0;
  scanf("%d%s", &n, s + 1);
  for (int i = 1; i <= n; ++i)
    if (s[i] == 'o')
      dp[i] = dp[i - 1] + 2 * m + 1, m = m + 1;
    else if (s[i] == 'x')
      dp[i] = dp[i - 1], m = 0;
    else
      dp[i] = dp[i - 1] + m + 0.5, m = 0.5 * (m + 1);
  printf("%.4lf\n", dp[n]);
  return 0;
}
