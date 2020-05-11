#include <cstdio>

int main() {
  int n, ans = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    ans += i * 2 - 1;
  for (int i = 1; i < n; ++i)
    ans += i * 2 - 1;
  printf("%d\n", ans);
  return 0;
}
