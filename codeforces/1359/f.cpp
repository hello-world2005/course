#include <cmath>
#include <cstdio>
const int N = 25010;
int n, m;
int x[N], y[N], dx[N], dy[N], s[N];
double c[N];
int main(void) {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d%d%d", &x[i], &y[i], &dx[i], &dy[i], &s[i]);
    c[i] = s[i] / sqrt(dx[i] * dx[i] + dy[i] * dy[i]);
  }
  double ans = 1e12;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= i - 1; ++j) {
      int flag = dx[j] * dy[i] - dx[i] * dy[j];
      int dey = y[j] - y[i];
      int dex = x[j] - x[i];
      if (flag != 0) {
        double t1 = 1.0 * (dx[j] * dey - dy[j] * dex) / (c[i] * flag);
        double t2 = 1.0 * (dx[i] * dey - dy[i] * dex) / (c[j] * flag);
        if (t1 >= 0 && t2 >= 0)
          ans = std::min(ans, std::max(t1, t2));
      } else if ((x[i] - x[j]) * dy[j] == (y[i] - y[j]) * dx[j]) {
        int v = 0;
        if (dex * dx[i] > 0)
          v += s[i];
        if (dex * dx[j] < 0)
          v += s[j];
        if (v > 0)
          ans = std::min(ans, 1.0 * sqrt(dex * dex + dey * dey) / v);
      }
    }
  }
  if (ans == 1e12)
    printf("No show :(\n");
  else
    printf("%.7f", ans);
  return 0;
}
