#include <cstdio>
#include <vector>

#define int long long

int Pow(int a, int b) {
  int res = 1;
  for (int i = 1; i <= b; ++i)
    res *= b;
  return res;
}

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int p, q, x;
    scanf("%lld%lld", &p, &q);
    if (p % q != 0) {
      printf("%lld\n", p);
    } else {
      std::vector<std::pair<int, int> > v1, v2;
      int t = p / q;
      for (int i = 2; i * i <= t; ++i)
        if (t % i == 0) {
          int _ = t, cnt = 0;
          while (_ % i == 0)
            _ /= i, ++cnt;
          v1.push_back(std::make_pair(i, cnt));
          if (i * i != t) {
            int _ = t, cnt = 0, j = t / i;
            while (_ % j == 0)
              _ /= j, ++cnt;
            v1.push_back(std::make_pair(j, cnt));
          }
        }
      for (int i = 2; i * i <= q; ++i)
        if (q % i == 0) {
          int _ = q, cnt = 0;
          while (_ % i == 0)
            _ /= i, ++cnt;
          v2.push_back(std::make_pair(i, cnt));
          if (i * i != t) {
            int _ = t, cnt = 0, j = q / i;
            while (_ % j == 0)
              _ /= j, ++cnt;
            v2.push_back(std::make_pair(j, cnt));
          }
        }
      // printf("%lld\n", (int)v2.size());
      if (v2.size() == 0) {
        int ans = p;
        while (ans % q == 0)
          ans /= q;
        printf("%lld\n", ans);
        continue;
      }
      long long ans = 0;
      for (int i = 0; i < (int)v2.size(); ++i) {
        int now = 1;
        int x = v2[i].first;
        printf(">> %lld\n", v2[i].first);
        now = q / x;
        for (int j = 0; j < (int)v1.size(); ++j)
          if (v1[j].first != x) {
            printf("%lld\n", v1[j].first);
            now *= Pow(v1[j].first, v1[j].second);
          }
        ans = std::max(ans, now);
      }
      // for (int i = 1; i < (int)v1.size(); ++i)
      //   if (v1[i] != x)
      //     ans *= v1[i];
      // for (int i = 0; i < (int)v2.size(); ++i)
      //   if (v1[i].first != x)
      //     ans *= Pow(v1[i].first, v1[i].second);
      printf("%lld\n", ans);
    }
  }
  return 0;
}
