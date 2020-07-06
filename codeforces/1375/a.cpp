#include <cstdio>
#include <cmath>

const int N = 110;

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, a[N];
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
      if (i & 1)
        printf("%d ", abs(a[i]));
      else
        printf("%d ", -abs(a[i]));
    printf("\n");
  }
  return 0;
}
