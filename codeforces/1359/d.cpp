#include <algorithm>
#include <cstdio>

#define int long long

const int N = 1e5 + 10;

int n;
int a[N];

signed main() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]);
  int ans = 0;
  for (int i = 0; i <= 30; ++i) {
    int sum = 0, minn = 0;
    for (int j = 1; j <= n; ++j) {
      sum += (a[j] > i ? -(int)3e6 : a[j]);
      minn = std::min(minn, sum);
      ans = std::max(ans, sum - minn - i);
      // printf("%lld %lld %lld\n", i, j, sum - minn - i);
    }
  }
  printf("%lld\n", ans);
  return 0;
}
