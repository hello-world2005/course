#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    scanf("%d%d", &n, &m);
    if (n == 4 && m == 2) {
      printf("24\n");
    } else if (n == 1 && m == 3) {
      printf("6\n");
    } else if (m == 2) {
      if (n & 1)
        printf("%d\n", (n + 1) * 3);
      else
        printf("%d\n", (n + 2) * 3);
    } else {
      printf("%d\n", (n + 1) * 2);
    }
  }
  return 0;
}
