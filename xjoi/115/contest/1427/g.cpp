#include <algorithm>
#include <cstdio>

const int N = 60;
const int M = 110;

int n, s;
double m;
double d[N];
int u[N];
double dp[N][M];
int pre[N][M];
double ans;

void Print(int now, int rem) {
  if (!now)
    return;
  Print(now - 1, pre[now][rem]);
  printf("%d ", u[now] + rem - pre[now][rem]);
}

int main() {
  scanf("%d%d%lf", &n, &s, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%lf", &d[i]);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &u[i]);
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j <= s; ++j)
      dp[i][j] = 1e12;
  for (int i = u[1]; i <= s + u[1]; ++i)
    dp[1][i - u[1]] = d[1] * i;
  for (int i = 2; i <= n; ++i)
    for (int j = 0; j <= s; ++j)
      for (int k = std::max(0, u[i] - j); j + k - u[i] <= s; ++k)
        if (dp[i][j + k - u[i]] > dp[i - 1][j] + k * d[i] + j * m) {
          dp[i][j + k - u[i]] = dp[i - 1][j] + k * d[i] + j * m;
          pre[i][j + k - u[i]] = j;
        }
  printf("%.1f\n", dp[n][0]);
  Print(n, 0);
  return 0;
}