#include <cmath>
#include <cstdio>
#include <ctime>
#include <random>

std::mt19937_64 rnd;

int main() {
  rnd.seed(time(NULL));
  unsigned long long n = rnd() % int(1e5) + 1, m = rnd() % int(1e5) + 1;
  printf("%llu %llu\n", n, m);
  for (int i = 1; i <= n; ++i)
    printf("%llu ", rnd() % (1ull << 60) + 1);
  printf("\n");
  for (int i = 1; i <= m; ++i) {
    bool flag = rnd() % 2ull;
    unsigned long long l = rnd() % n + 1;
    unsigned long long r;
    if (flag)
      r = (l + rnd() % int(sqrt(n))) % n + 1;
    else
      r = rnd() % n + 1;
    printf("%llu %llu\n", l, r);
  }
  return 0;
}
