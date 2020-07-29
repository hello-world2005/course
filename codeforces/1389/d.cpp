#include <algorithm>
#include <cmath>
#include <cstdio>

#define int long long

int Calc(int l1, int r1, int l2, int r2) {
  return std::max(r1 - l2, 0ll);
}

const int N = 2e5 + 10;

int l1[N], r1[N], l2[N], r2[N];

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int n, k;
    scanf("%lld%lld", &n, &k);
    scanf("%lld%lld%lld%lld", &l1[0], &r1[0], &l2[0], &r2[0]);
    if (l1[0] > l2[0])
      std::swap(l1[0], l2[0]), std::swap(r1[0], r2[0]);
    // int ans = 0, qwq = 0;
    // if (r1 < l2) {
    //   ans += (l2 - r1) * n;
    //   qwq = l2 - r1;
    //   r1 = l2;
    // }
    // int init = Calc(l1, r1, l2, r2) * n;
    // int emax = (l2 - l1) + std::max(r1, r2) - std::min(r1, r2);
    // printf("> %lld %lld\n", init, emax);
    // if (init >= k) {
    //   printf("0\n");
    // } else if (k <= init + n * emax) {
    //   int t = k - init;
    //   int tt = ceil(1.0 * t / emax);
    //   if (qwq)
    //     ans -= (n - tt) * qwq;
    //   printf("%lld\n", ans + t);
    // } else {
    //   int t = init + n * emax;
    //   int tt = k - t;
    //   printf("%lld\n", ans + t + tt * 2);
    // }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
      l1[i] = l1[0], r1[i] = r1[0], l2[i] = l2[0], r2[i] = r2[0];
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
      int init = Calc(l1[i], r1[i], l2[i], r2[i]), qwq = 0;
      if (r1[i] < l2[i])
        qwq = l2[i] - r1[i], r1[i] = l2[i];
      int emax =
          (l2[i] - l1[i]) + std::max(r1[i], r2[i]) - std::min(r1[i], r2[i]);
      // printf("emax%lld\n", emax);
      sum += init + emax;
      ans += qwq + emax;
      if (sum < k) {
        int qaq = k - sum;
        // if (qaq * 2 <= qwq) {
        //   ans += qaq * 2;
        //   sum = k;
        //   break;
        // }
      }
      if (sum >= k) {
        // printf("> %lld\n", i);
        if (sum - emax >= k)
          ans -= emax;
        else
          ans -= sum - k;
        break;
      }
    }
    // printf("> %lld\n", sum);
    if (sum >= k) {
      printf("%lld\n", ans);
      continue;
    }
    printf("%lld\n", ans + (k - sum) * 2);
  }
  return 0;
}
