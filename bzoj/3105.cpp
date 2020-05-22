#include <algorithm>
#include <cstdio>
#include <functional>

#define int long long

const int N = 110;
const int K = 32;

int n;
int a[N];
int d[K];

bool Insert(int k) {
  for (int i = K - 1; i >= 0; --i)
    if (k >> i & 1ll) {
      if (!d[i]) {
        d[i] = k;
        return true;
      } else {
        k ^= d[i];
      }
    }
  return false;
}

signed main() {
  scanf("%lld", &n);
  int sum = 0;
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]), sum += a[i];
  std::sort(a + 1, a + n + 1, std::greater<int>());
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    if (!Insert(a[i]))
      ans += a[i];
  if (ans != sum)
    printf("%lld\n", ans);
  else
    printf("-1\n");
  return 0;
}
