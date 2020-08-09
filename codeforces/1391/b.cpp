#include <cstdio>

const int N = 110;

char s[N][N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m, cnt = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
      scanf("%s", s[i] + 1);
    for (int i = 1; i <= n; ++i)
      if (s[i][m] == 'R')
        ++cnt;
    for (int i = 1; i <= m; ++i)
      if (s[n][i] == 'D')
        ++cnt;
    printf("%d\n", cnt);
  }
  return 0;
}
