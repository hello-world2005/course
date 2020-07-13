#include <cstdio>
#include <cstdlib>
#include <ctime>

int Random(int l, int r) {
  return rand() * rand() % (r - l + 1) + l;
}

int main() {
  srand(time(NULL));
  int n = Random(1, 114514), m = Random(1, 114514);
  printf("%d %d\n", n, m);
  while (m--)
    printf("%d %d %d\n", Random(1, 2), Random(1, n), Random(1, n));
  return 0;
}
