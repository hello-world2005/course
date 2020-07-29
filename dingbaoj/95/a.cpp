#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 16;
const int M = 1010;
const int MOD = 1e9 + 7;

int dp[M][1 << N], lcs[1 << N][4];
int ans[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    memset(dp, 0, sizeof(dp));
    memset(lcs, 0, sizeof(lcs));
    memset(ans, 0, sizeof(ans));
    char s[20];
    int m, n, a[20];
    scanf("%s%d", s + 1, &m);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i)
      if (s[i] == 'A')
        a[i] = 0;
      else if (s[i] == 'C')
        a[i] = 1;
      else if (s[i] == 'G')
        a[i] = 2;
      else if (s[i] == 'T')
        a[i] = 3;

    auto Lcs = [=](int mask, int k) {
      int lc[2][N];
      memset(lc, 0, sizeof(lc));
      int res = 0;
      for (int i = 0; i < n; ++i)
        lc[0][i + 1] = lc[0][i] + (mask >> i & 1);
      for (int i = 1; i <= n; ++i) {
        int maxn = 0;
        if (a[i] == k)
          maxn = lc[0][i - 1] + 1;
        maxn = std::max({maxn, lc[0][i], lc[1][i - 1]});
        lc[1][i] = maxn;
      }
      for (int i = 1; i <= n; ++i)
        res += (1 << (i - 1)) * (lc[1][i] - lc[1][i - 1]);
      return res;
    };

    for (int mask = 0; mask < (1 << n); ++mask)
      for (int i = 0; i < 4; ++i)
        lcs[mask][i] = Lcs(mask, i);
    dp[0][0] = 1;
    for (int i = 1; i <= m; ++i)
      for (int mask = 0; mask < (1 << n); ++mask)
        for (int j = 0; j < 4; ++j)
          dp[i][lcs[mask][j]] = (dp[i][lcs[mask][j]] + dp[i - 1][mask]) % MOD;
    for (int mask = 0; mask < (1 << n); ++mask)
      ans[__builtin_popcount(mask)] =
          (ans[__builtin_popcount(mask)] + dp[m][mask]) % MOD;
    for (int i = 0; i <= n; ++i)
      printf("%d\n", ans[i]);
  }
  return 0;
}
