// 1 2 3 5 8

#include <algorithm>
#include <cstdio>

#define int long long

int fib[1000], cnt;

signed main() {
  int T;
  scanf("%lld", &T);
  fib[1] = 1, fib[2] = 2;
  for (cnt = 3; fib[cnt - 1] <= (int)1e18; ++cnt)
    fib[cnt] = fib[cnt - 1] + fib[cnt - 2];
  --cnt;
  while (T--) {
    int n, k;
    scanf("%lld%lld", &n, &k);
    if (n < k) {
      printf("No\n");
      continue;
    }
    int sum = 0;
    while (n > 0) {
      int p = std::upper_bound(fib + 1, fib + cnt + 1, n) - fib - 1;
      int s = fib[p];
      // printf("%lld\n", s);
      if (n >= s)
        n -= s, ++sum;
      else
        break;
    }
    printf("%s\n", (sum <= k && n == 0) ? "Yes" : "No");
  }
  return 0;
}
