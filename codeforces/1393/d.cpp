#include <algorithm>
#include <cstdio>

const int N = 2010;

int n, m;
char s[N][N];
int a[N][N], b[N][N], c[N][N], d[N][N];

int Solve(int x, int y) {
  return std::min({a[x][y], b[x][y], c[x][y], d[x][y]});
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%s", s[i] + 1);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (s[i][j] == s[i - 1][j] && s[i][j] == s[i][j - 1])
        a[i][j] = std::min(a[i - 1][j], a[i][j - 1]) + 1;
      else
        a[i][j] = 1;
  for (int i = 1; i <= n; ++i)
    for (int j = m; j >= 1; --j)
      if (s[i][j] == s[i - 1][j] && s[i][j] == s[i][j + 1])
        b[i][j] = std::min(b[i - 1][j], b[i][j + 1]) + 1;
      else
        b[i][j] = 1;
  for (int i = n; i >= 1; --i)
    for (int j = 1; j <= m; ++j)
      if (s[i][j] == s[i + 1][j] && s[i][j] == s[i][j - 1])
        c[i][j] = std::min(c[i + 1][j], c[i][j - 1]) + 1;
      else
        c[i][j] = 1;
  for (int i = n; i >= 1; --i)
    for (int j = m; j >= 1; --j)
      if (s[i][j] == s[i + 1][j] && s[i][j] == s[i][j + 1])
        d[i][j] = std::min(d[i + 1][j], d[i][j + 1]) + 1;
      else
        d[i][j] = 1;
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      ans += Solve(i, j);
  printf("%d\n", ans);
  return 0;
}
