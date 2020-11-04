#include <cstdio>

#define int long long

signed main() {
  int a, b;
  scanf("%lld%lld", &a, &b);
  printf("%lld\n", a * b - a - b);
  return 0;
}
