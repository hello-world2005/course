#include <cstdio>
#include <cstring>

const int N = 110;
const int M = 1010;

int n, m, x, y;
char a[N][M];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &n, &m, &x, &y);
    for (int i = 1; i <= n; ++i)
      scanf("%s", a[i] + 1), a[i][m + 1] = '*';
    if (y > 2 * x)
      y = 2 * x;
    int ans = 0;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        if (a[i][j] == '.' && a[i][j + 1] == '.')
          ans += y, a[i][j + 1] = a[i][j] = '*';
        else if (a[i][j] == '.')
          ans += x, a[i][j] = '*';
    printf("%d\n", ans);
  }
  return 0;
}
