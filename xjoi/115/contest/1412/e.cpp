#include <algorithm>
#include <cstdio>
#include <cstring>

const int M = 1010;
const int N = 1e5 + 10;
const int Q = 110;

int t, m, n;
struct Class {
  int t, s, c;

  Class() : t(0), s(0), c(0) {}

  bool operator<(const Class& rhs) const { return t < rhs.t; }
} cla[M];
int a[N], q[N];
int dp[N][Q];
int minn[Q];

int main() {
  scanf("%d%d%d", &t, &m, &n);
  for (int i = 1; i <= m; ++i)
    scanf("%d%d%d", &cla[i].t, &cla[i].s, &cla[i].c);
  memset(dp, -0x3f, sizeof(dp));
  dp[0][1] = 0;
  memset(minn, 0x3f, sizeof(minn));
  for (int i = 1; i <= n; ++i)
    scanf("%d%d", &a[i], &q[i]), minn[q[i]] = std::min(a[i], minn[q[i]]);
  for (int i = 1; i <= 100; ++i)
    minn[i] = std::min(minn[i], minn[i - 1]);
  std::sort(cla + 1, cla + m + 1);
  for (int i = 1, p = 1; i <= t; ++i) {
    for (int j = 1; j <= 100; ++j)
      if (dp[i][j] < 0)
        dp[i][j] = dp[i - 1][j];
    while (cla[p].t == i) {
      int x = i, y = x + cla[p].s - 1, z = cla[p].c;
      dp[y][z] = 0;
      for (int j = 1; j <= 100; ++j)
        dp[y][z] = std::max(dp[i - 1][j], dp[y][z]);
      ++p;
    }
    for (int j = 1; j <= 100; ++j) {
      if (i - minn[j] < 0 || minn[j] == 0x3f3f3f3f)
        continue;
      if (dp[i - minn[j]][j] >= 0)
        dp[i][j] = std::max(dp[i][j], dp[i - minn[j]][j] + 1);
    }
  }
  int ans = 0;
  for (int i = 1; i <= 100; ++i)
    ans = std::max(ans, dp[t][i]);
  printf("%d\n", ans);
  return 0;
}
