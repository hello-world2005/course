#include <algorithm>
#include <cstdio>

#define int long long

int get(int x) {
  int minn = 11, maxn = -1;
  while (x) {
    int t = x % 10;
    x /= 10;
    minn = std::min(minn, t);
    maxn = std::max(maxn, t);
  }
  return minn * maxn;
}

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int a, k, b;
    scanf("%lld%lld", &a, &k);
    for (int i = 1; i < k; ++i) {
      b = get(a);
      if (b == 0)
        break;
      a += b;
    }
    printf("%lld\n", a);
  }
  return 0;
}
