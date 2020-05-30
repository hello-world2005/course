#include <cstdio>
#include <cstdlib>
#include <ctime>

int main() {
  srand(time(NULL));
  int n = rand() % 10 + 1, q = rand() % 10 + 1;
  printf("%d %d\n", n, q);
  for (int i = 1; i <= n; ++i)
    printf("%d ", rand() % 10 + 1);
  printf("\n");
  for (int i = 1; i < n; ++i)
    printf("%d ", rand() % i + 1);
  printf("\n");
  while (q--)
    printf("%d %d\n", rand() % n + 1, rand() % 10 + 1);
  return 0;
}
