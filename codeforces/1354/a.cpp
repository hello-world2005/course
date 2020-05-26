#include <cmath>
#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    long long a, b, c, d;
    scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
    if (a <= b) {
      printf("%lld\n", b);
    } else if (c <= d) {
      printf("-1\n");
    } else {
      printf("%lld\n", b + ((a - b - 1) / (c - d) + 1) * c);
    }
  }
  return 0;
}
