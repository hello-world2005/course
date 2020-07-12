#include <algorithm>
#include <cstdio>

#define int long long

const int MOD = 998244353;

const int N = 3e5 + 10;

int a[N], sum[N], ans[N];

int FastPow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = a * a % MOD)
    if (b & 1)
      res = res * a % MOD;
  return res;
}

signed main() {
  int n;
  scanf("%lld", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]);
  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; ++i)
    sum[i] = sum[i - 1] + a[i];
  for (int i = 1; i < n; ++i) {
    for (int j = i; j > 0; j -= (n - i))
      ans[i] = (ans[i] + sum[j]) % MOD;
  }
  for (int i = n - 1; i >= 0; i--)
    printf("%lld ", ans[i] * FastPow(n, MOD - 2) % MOD);
  printf("\n");
  return 0;
}