#include <cstdio>

const int N = 1010;

int a[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    int maxn = 0, pos = 0;
    bool flag = false;
    for (int i = 2; i < n; ++i) {
      int p1 = 0, p2 = 0;
      for (int j = 1; j < i; ++j)
        if (a[j] < a[i]) {
          p1 = j;
          break;
        }
      for (int j = i + 1; j <= n; ++j)
        if (a[j] < a[i]) {
          p2 = j;
          break;
        }
      if (p1 && p2) {
        printf("YES\n%d %d %d\n", p1, i, p2);
        flag = true;
        break;
      }
    }
    if (!flag)
      printf("NO\n");
  }
  return 0;
}
