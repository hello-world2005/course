#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int l, r;
    scanf("%d%d", &l, &r);
    if (2 * l <= r)
      printf("%d %d\n", l, 2 * l);
    else
      printf("-1 -1\n");
  }
  return 0;
}
