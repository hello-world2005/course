#include <cstdio>

#define int long long

int Gcd(int a, int b) {
  if (b == 0)
    return a;
  return Gcd(b, a % b);
}

int Phi(int x) {
  int res = x;
  for (int i = 2; i * i <= x; ++i)
    if (x % i == 0) {
      res = res / i * (i - 1);
      while (x % i == 0)
        x /= i;
    }
  if (x != 1)
    res = res / x * (x - 1);
  return res;
}

signed main() {
  int T;
  // printf("%lld\n", Phi(9));
  scanf("%lld", &T);
  while (T--) {
    int a, b;
    scanf("%lld%lld", &a, &b);
    int d = Gcd(a, b);
    printf("%lld\n", Phi(b / d));
  }
  return 0;
}
