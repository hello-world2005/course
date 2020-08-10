#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<std::pair<int, int> > a(n);
  for (auto &i : a)
    scanf("%d%d", &i.first, &i.second);
  std::vector<std::pair<int, int> > p, q;
  for (auto i : a)
    if (i.second > 0)
      p.push_back(i);
    else
      q.push_back(i);
  std::sort(p.begin(), p.end());
  int ans = 0;
  for (auto i : p)
    if (i.first > m)
      break;
    else
      m += i.second, ++ans;
  std::vector<std::vector<int> > dp(q.size());
  for (auto &i : dp)
    i.resize(m + 1);
  std::sort(q.begin(), q.end(), [&](const auto lhs, const auto rhs) { return lhs.first + lhs.second > rhs.first + rhs.second; });
  int res = 0;
  for (int i = 0; i < (int)q.size(); ++i)
    if (m >= q[i].first && m >= -q[i].second) {
      dp[i][m + q[i].second] = 1;
      res = std::max(res, dp[i][m + q[i].second]);
      for (int j = i - 1; j >= 0; --j)
        for (int k = std::max(q[i].first, -q[i].second); k <= m; ++k)
          if (dp[j][k]) {
            dp[j][k + q[i].second] = std::max(dp[j][k + q[i].second], dp[j][k] + 1);
            res = std::max(res, dp[j][k + q[i].second]);
          }
    }
  printf("%d\n", ans + res);
  return 0;
}
