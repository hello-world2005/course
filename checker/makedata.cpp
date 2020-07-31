#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>

int Random(int l, int r) {
  return rand() % (r - l + 1) + l;
}

int main() {
  srand(time(0));
  int n = Random(1, 1000), m = Random(1, 1000);
  printf("%d %d ", n, m);
  for (int i = 1; i <= m; ++i)
    printf("%d ", Random(1, n));
  for (int i = 2; i <= n; ++i)
    printf("%d ", Random(1, i - 1));
  return 0;
}
