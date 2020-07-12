#include <cstdio>
#include <cstdlib>
#include <ctime>

int Random(int l, int r) {
  return rand() % (r - l + 1) + l;
}

int main() {
  srand(time(NULL));
  int n = Random(1, 10), m = Random(1, 100);
  printf("%d\n", n);
  for (int i = 2; i <= n; ++i)
    printf("%d %d\n", i, Random(1, i - 1));
  printf("%d\n", m);
  while (m--)
    printf("%d %d\n", Random(0, 1), Random(1, n));
  return 0;
}
