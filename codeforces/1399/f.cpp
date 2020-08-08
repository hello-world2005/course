#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 6010;

int dp[N][N];
std::vector<std::vector<int> > seg;

int Dfs(int l, int r) {  // DP
  // printf("> %d %d\n", l, r);
  if (l > r)
    return 0;
  if (~dp[l][r])
    return dp[l][r];
  int vis = std::count(seg[l].begin(), seg[l].end(), r);
  dp[l][r] = std::max(0, Dfs(l + 1, r) + vis);
  if (vis)
    vis = 1;
  for (auto i : seg[l]) {
    if (i >= r)
      continue;
    dp[l][r] = std::max(dp[l][r], Dfs(l, i) + Dfs(i + 1, r) + vis);
  }
  return dp[l][r];
}

int main() {
  int T;
  scanf("%d", &T);
  memset(dp, -1, sizeof(dp));
  while (T--) {
    int n;
    scanf("%d", &n);
    std::vector<int> l(n), r(n);
    std::vector<int> val;
    for (int i = 0; i < n; ++i)
      scanf("%d%d", &l[i], &r[i]), val.push_back(l[i]), val.push_back(r[i]);
    std::sort(val.begin(), val.end());
    val.erase(std::unique(val.begin(), val.end()), val.end());
    for (int i = 0; i < n; ++i)
      l[i] = std::lower_bound(val.begin(), val.end(), l[i]) - val.begin(),
      r[i] = std::lower_bound(val.begin(), val.end(), r[i]) - val.begin();
    seg = std::vector<std::vector<int> >(val.size());
    for (int i = 0; i < n; ++i)
      seg[l[i]].push_back(r[i]);
    printf("%d\n", Dfs(0, val.size() - 1));
    seg.clear();
    for (int i = 0; i < (int)val.size(); ++i)
      for (int j = 0; j < (int)val.size(); ++j)
        dp[i][j] = -1;
  }
  return 0;
}
