#include <algorithm>
#include <cstdio>

/*
 W W
WBWBW
 W W
*/

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m, p = 2, t = 1, y = 2;
    scanf("%d%d", &n, &m);
    int i = std::min(n, m), j = std::max(n, m);
    if (j > 3 * i + 1) {
      puts("NO");
    } else {
      puts("YES");
      if (n < m)
        ++y;
      while (i > 0)
        printf("%d %d\n", p, y), p += 2, i--;
      while (j > 0 && t < p)
        printf("%d %d\n", t, y), t += 2, j--;
      t = 2;
      while (j > 0 && t < p - 1)
        printf("%d %d\n", t, y - 1), t += 2, j--;
      t = 2;
      while (j > 0)
        printf("%d %d\n", t, y + 1), t += 2, j--;
    }
  }
  return 0;
}
