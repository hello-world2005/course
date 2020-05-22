#include <cstdio>

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i)
    printf("%c", (i % ((n - k) / 2 + 1)) > 0 ? '1' : '0');
  return 0;
}
