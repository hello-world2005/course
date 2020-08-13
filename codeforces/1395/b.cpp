#include <cstdio>

int main() {
  int n, m, x, y;
  scanf("%d%d%d%d", &n, &m, &x, &y);
  printf("%d %d\n", x, y);
  for (int i = 1; i <= n; ++i)
    if (i != x)
      printf("%d %d\n", i, y);
  bool flag = false;
  for (int i = 1; i <= m; ++i)
    if (i != y) {
      if (flag)
        for (int j = 1; j <= n; ++j)
          printf("%d %d\n", j, i);
      else
        for (int j = n; j >= 1; --j)
          printf("%d %d\n", j, i);
      flag ^= 1;
    }
  return 0;
}
