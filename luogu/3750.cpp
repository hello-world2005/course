#include <cstdio>
#include <vector>

const int N = 1e5 + 10;
const int MOD = 1e5 + 3;

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  std::vector<int> a(n + 1), inv(n + 1);
  inv[0] = inv[1] = 1;
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  for (int i = 2; i <= n; ++i)
    inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
  // printf("%d\n", inv[2]);
  std::vector<std::vector<int> > d(n + 1);
  for (int i = 1; i <= n; ++i)
    for (int j = i; j <= n; j += i)
      d[j].push_back(i);
  int cnt = 0;
  for (int i = n; i >= 1; --i)
    if (a[i]) {
      for (int j : d[i])
        a[j] ^= 1;
      ++cnt;
    }
  // printf("%d\n", cnt);
  int ans = 0;
  if (cnt <= k) {
    ans = cnt;
  } else {
    std::vector<int> dp(n + 1);
    dp[n] = 1;
    for (int i = n - 1; i >= 1; --i)
      dp[i] = (1 + 1ll * (n - i) * inv[i] % MOD * (dp[i + 1] + 1) % MOD) % MOD;
    for (int i = cnt; i > k; --i)
      ans = (ans + dp[i]) % MOD;
    (ans += k) %= MOD;
  }
  for (int i = 1; i <= n; ++i)
    ans = 1ll * ans * i % MOD;
  printf("%d\n", ans);
  return 0;
}
