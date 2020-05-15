#include <cstdio>
#include <cstdlib>
#include <ctime>

const int N = 50000;

int main() {
  srand(time(NULL));
  int n = rand() % N + 1, m = rand() % N + 1;
  printf("%d %d\n", n, m);
  const int opt[] = {1, 2, 3, 6};
  while (m--) {
    int o = opt[rand() % 4];
    int l = rand() % n + 1, r = rand() % (n - l + 1) + l;
    printf("%d %d %d", o, l, r);
    if (o == 1 || o == 2 || o == 3) {
      printf(" %d\n", rand() * rand());
    } else {
      printf("\n");
    }
  }
  return 0;
}
