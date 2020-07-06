#include <cstdio> 

typedef long long ll;

int main() {
  ll p, q, win, a[3] = {0, 0, 0};
  scanf("%lld%lld%lld", &a[0], &a[1], &a[2]);
  printf("First\n");
  fflush(stdout);
  printf("%lld\n", a[0] + a[1] + a[2]);
  fflush(stdout);
  scanf("%lld", &p);
  a[--p] += a[0] + a[1] + a[2];
  printf("%lld\n", a[p] * 3 - a[0] - a[1] - a[2]);
  fflush(stdout);
  scanf("%lld", &q);
  a[--q] += a[p] * 3 - a[0] - a[1] - a[2];
  printf("%lld\n", a[q] - a[p]);
  fflush(stdout);
  scanf("%lld", &win);
  return 0;
}