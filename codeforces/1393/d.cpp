#include <cstdio>

const int N = 2010;

int n, m;
char s[N][N];
int a[N][N], b[N][N];

int Solve(int x, int y) {}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%s", s[i] + 1);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (s[i][j] == s[i][j - 1]) {
      } else {
        a[i][j] = 1;
      }
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      ans += Solve(i, j);
  printf("%d\n", ans);
  return 0;
}
