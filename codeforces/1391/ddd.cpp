#include <algorithm>
#include <cstdio>
#include <vector>

const int N = 1e6 + 10;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  if (n >= 4 && m >= 4) {
    printf("-1\n");
  } else if (n == 1 || m == 1) {
    printf("0\n");
  } else if (n == 2) {
    std::vector<std::vector<int> > a(n + 1);
    static int dp[N][4];
    for (int i = 1; i <= n; ++i)
      a[i].resize(m + 1);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        scanf("%1d", &a[i][j]);
    for (int i = 1; i <= m; ++i) {
      dp[i][0] = std::min(dp[i - 1][1], dp[i - 1][2]),
      dp[i][1] = std::min(dp[i - 1][0], dp[i - 1][3]),
      dp[i][2] = std::min(dp[i - 1][0], dp[i - 1][3]),
      dp[i][3] = std::min(dp[i - 1][1], dp[i - 1][2]);
      if (a[1][i] == 1)
        ++dp[i][0], ++dp[i][1];
      else
        ++dp[i][2], ++dp[i][3];
      if (a[2][i] == 1)
        ++dp[i][0], ++dp[i][2];
      else
        ++dp[i][1], ++dp[i][3];
    }
    printf("%d\n", std::min({dp[m][0], dp[m][1], dp[m][2], dp[m][3]}));
  } else if (n == 3) {}
}
