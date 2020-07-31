#include <algorithm>
#include <cstdio>
#include <cstring>

#define int long long

const int MOD = 1e9 + 7;

namespace Subtask1 {

int a[70], len;
int dp[70][70];

int Dfs(int now, int cnt, bool ismax, bool zero) {
  if (now > len)
    return (1ll << cnt) % MOD;
  if (!ismax && !zero && ~dp[now][cnt])
    return dp[now][cnt];
  int lim = ismax ? a[now] : 1, res = 0;
  for (int i = 0; i <= lim; ++i) {
    if (i == 1)
      res = (res + Dfs(now + 1, cnt + 1, ismax && i == lim, zero && i == 0)) %
            MOD;
    else
      res = (res + Dfs(now + 1, cnt, ismax && i == lim, zero && i == 0)) % MOD;
  }
  if (!ismax && !zero)
    dp[now][cnt] = res;
  return res;
}

int Solve(int x) {
  len = 0;
  while (x) {
    a[++len] = x & 1;
    x >>= 1;
  }
  std::reverse(a + 1, a + len + 1);
  memset(dp, -1, sizeof(dp));
  return Dfs(1, 0, true, true);
}

void Main(int T) {
  while (T--) {
    int l, r;
    scanf("%lld%lld", &l, &r);
    printf("%lld\n", (Solve(r) - Solve(l - 1) + MOD) % MOD);
  }
}
}  // namespace Subtask1

signed main() {
  int T, k;
  scanf("%lld%lld", &T, &k);
  if (k == 0) {
    Subtask1::Main(T);
    return 0;
  }
}