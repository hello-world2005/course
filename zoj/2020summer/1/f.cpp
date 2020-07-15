#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <unordered_map>

const int N = 1e5 + 10;

std::mt19937 rnd(time(NULL));
double n, p;
double x[N], y[N];
double cnt;

bool FindPoint() {
  int now = rnd() % ((int)n) + 1, sum = 0;
  std::unordered_map<double, int> mp;
  for (int i = 1; i <= n; ++i) {
    if (i == now)
      continue;
    int tot = ++mp[(y[i] - y[now]) / (x[i] - x[now])];
    sum = std::max(sum, tot);
  }
  if (sum + 1 >= cnt)
    return true;
  return false;
}

bool Solve() {
  if (FindPoint())
    return true;
  clock_t tim = clock(), once = clock();
  while (((double)tim) / CLOCKS_PER_SEC <
         0.9 - ((double)once) / CLOCKS_PER_SEC) {
    if (FindPoint())
      return true;
    tim = clock();
  }
  return false;
}

signed main() {
  scanf("%lf%lf", &n, &p);
  for (int i = 1; i <= n; ++i)
    scanf("%lf%lf", &x[i], &y[i]);
  cnt = ceil(1.0 * n / 100 * p);
  printf("%s\n", Solve() ? "possible" : "impossible");
  return 0;
}
