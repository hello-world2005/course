#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>

int Random(int l, int r) {
  return rand() % (r - l + 1) + l;
}

int main() {
  srand(time(0));
  int n = Random(1, 10), m = Random(1, 10);
  printf("%d %d\n", n, m);
  for (int i = 1; i <= n; ++i)
    printf("%d ", Random(1, 10));
  printf("\n");
  for (int i = 1; i <= m; ++i) {
    int opt = Random(1, 3), l, r;
    if (opt >= 2)
      l = Random(1, n), r = Random(l, n);
    else
      l = Random(1, n), r = Random(1, 10);
    printf("%d %d %d\n", opt, l, r);
  }
  return 0;
}
