#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>

int Random(int l, int r) {
  return rand() * rand() % (r - l + 1) + l;
}

int main() {
  srand(time(0));
  int n = Random(1, 30000);
  printf("%d\n", n);
  for (int i = 1; i <= n; ++i)
    printf("%d\n", Random(0, n - 1));
  return 0;
}
