#include <algorithm>
#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, x, a[60], b[60];
    scanf("%d%d", &n, &x);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &b[i]);
    std::sort(a + 1, a + n + 1);
    std::sort(b + 1, b + n + 1);
    std::reverse(b + 1, b + n + 1);
    bool flag = true;
    for (int i = 1; i <= n; ++i)
      if (a[i] + b[i] > x) {
        flag = false;
        break;
      }
    printf("%s\n", flag ? "yes" : "no");
  }
  return 0;
}
