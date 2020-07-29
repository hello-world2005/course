#include <algorithm>
#include <cstdio>

#define int long long

int Gcd(int a, int b) {
  if (b == 0)
    return a;
  return Gcd(b, a % b);
}

signed main() {
  int T;
  scanf("%lld", &T);
  while (T--) {
    int m, d, w;
    scanf("%lld%lld%lld", &m, &d, &w);
    int gcd = Gcd(d - 1, w);
    int k = w / gcd;  // k | x - y
    int lim = std::min(m, d);
    int n = lim / k;
    printf("%lld\n", (lim - n * k + lim - k) * n / 2);
  }
  return 0;
}
