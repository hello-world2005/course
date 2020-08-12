#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    if (n % 4) {
      printf("NO\n");
      continue;
    }
    printf("YES\n");
    int sum1 = 0, sum2 = 0;
    for (int i = 1; i <= n / 2; ++i)
      printf("%d ", i * 2), sum1 += i * 2;
    for (int i = 1; i <= n / 2 - 1; ++i)
      printf("%d ", i * 2 - 1), sum2 += i * 2 - 1;
    printf("%d\n", sum1 - sum2);
  }
  return 0;
}
