#include <cstdio>

const int N = 310;

int a[N][N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        scanf("%d", &a[i][j]);
    bool flag = false;
    if (a[1][1] > 2 || a[n][1] > 2 || a[1][m] > 2 || a[n][m] > 2)
      flag = true;
    for (int i = 2; i < n; ++i)
      if (a[i][1] > 3 || a[i][m] > 3) {
        flag = true;
        break;
      }
    for (int i = 2; i < m; ++i)
      if (a[1][i] > 3 || a[n][i] > 3) {
        flag = true;
        break;
      }
    for (int i = 2; i < n; ++i)
      for (int j = 2; j < m; ++j)
        if (a[i][j] > 4) {
          flag = true;
          break;
        }
    if (flag) {
      printf("NO\n");
      continue;
    }
    a[1][1] = a[n][1] = a[1][m] = a[n][m] = 2;
    for (int i = 2; i < n; ++i)
      a[i][1] = a[i][m] = 3;
    for (int i = 2; i < m; ++i)
      a[1][i] = a[n][i] = 3;
    for (int i = 2; i < n; ++i)
      for (int j = 2; j < m; ++j)
        a[i][j] = 4;
    printf("YES\n");
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j)
        printf("%d ", a[i][j]);
      printf("\n");
    }
  }
  return 0;
}
