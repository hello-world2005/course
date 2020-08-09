#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    if (n & 1) {
    for (int i = 1; i <= n; ++i)
      if (i & 1)
        printf("%d ", i);
      else
        printf("%d ", n - (i - 1));
    } else {
      for (int i = 1; i <= n; ++i)
        if (i & 1)
          printf("%d ", n - (i / 2));
        else
          printf("%d ", i / 2);
    }
    printf("\n");
  }
  return 0;
}
