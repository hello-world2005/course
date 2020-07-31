#include <algorithm>
#include <cstdio>

#define int long long

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int n, k;
    scanf("%lld%lld", &n, &k);
    int l1, r1, l2, r2;
    scanf("%lld%lld%lld%lld", &l1, &r1, &l2, &r2);
    if (r1 > r2)
      std::swap(l1, l2), std::swap(r1, r2);
    if (r1 < l2) {
      if (k <= r2 - l1)
        printf("%lld\n", k + l2 - r1);
      else if (k <= (r2 - l1) * n)
        printf("%lld\n",
               (k / (r2 - l1)) * (r2 - l1 + l2 - r1) +
                   std::min((k - (k / (r2 - l1)) * (r2 - l1)) * 2,
                            l2 - r1 + (k - (k / (r2 - l1)) * (r2 - l1))));
      else
        printf("%lld\n", (r2 - l1 + l2 - r1) * n + (k - (r2 - l1) * n) * 2);
    } else {
      if (l2 < l1) {
        if (k <= (r1 - l1) * n)
          printf("0\n");
        else if (k <= (r2 - l2) * n)
          printf("%lld\n", k - (r1 - l1) * n);
        else
          printf("%lld\n", (k - (r2 - l2) * n) * 2 + (l1 - l2 + r2 - r1) * n);
      } else {
        if (k <= (r1 - l2) * n)
          printf("0\n");
        else if (k <= (r2 - l1) * n)
          printf("%lld\n", k - (r1 - l2) * n);
        else
          printf("%lld\n", (k - (r2 - l1) * n) * 2 + (l2 - l1 + r2 - r1) * n);
      }
    }
  }
}
