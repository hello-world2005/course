#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>

int Random(int l, int r) {
  return rand() * rand() % (r - l + 1) + l;
}

int main() {
  srand(time(0));
  printf("1\n");
  int n = Random(1, 2e5);
  printf("%d\n", n);
  for (int i = 1; i <= n; ++i)
    printf("%d ", Random(1, 2e5));
  printf("\n");
  return 0;
}
