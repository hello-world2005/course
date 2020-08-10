#include <algorithm>
#include <cstdio>

/*
  W
 WBW
WBWBW
 WBW
  W

 W W
WBWBW
 W W
*/

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    scanf("%d%d", &n, &m);
    if (n == m) {
      printf("YES\n");
      for (int i = 1; i <= n + m; ++i)
        printf("%d %d\n", 1, i);
    } else {
      bool flag = n < m ? 1 : 0;
      if (n < m)
        std::swap(n, m);
      int l = (n - m) / 2;
      if (n - 2 * m > 1) {
        printf("NO\n");
        continue;
      }
      n -= m;
      for (int i = 1; i <= n; ++i)
    }
  }
  return 0;
}
