#include <cstdio>

int main() {
  int n, s;
  scanf("%d%d", &n, &s);
  if (2 * n > s) {
    printf("NO\n");
    return 0;
  } else {
    printf("YES\n");
    for (int i = 1; i < n; ++i)
      printf("1 ");
    printf("%d\n", s - n + 1);
    printf("%d\n", s / 2);
  }
  return 0;
}
