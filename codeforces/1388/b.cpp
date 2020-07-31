#include <cstdio>
#include <cmath>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      if (i <= n - ceil(n / 4.0))
        printf("9");
      else
        printf("8");
    printf("\n");
  }
  return 0;
}
