#include <cstdio>
#include <cstring>

const int N = 120;

int a[N], b[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    memset(b, 0, sizeof(b));
    int n;
    scanf("%d", &n);
    n *= 2;
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
      if (!b[a[i]])
        printf("%d ", a[i]), b[a[i]] = 1;
    printf("\n");
  }
  return 0;
}
