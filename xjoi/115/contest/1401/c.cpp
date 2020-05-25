#include <bits/stdc++.h>
using namespace std;
inline int rd() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
    x = x * 10 + ch - '0', ch = getchar();
  return x * f;
}
const int N = 50005;
int a[N], n, m, mx[18][N], mn[18][N], lg[N], bin[18];
inline int ask(int l, int r) {
  if (l > r)
    swap(l, r);
  int x = lg[r - l + 1];
  return max(mx[x][l], mx[x][r - bin[x] + 1]) -
         min(mn[x][l], mn[x][r - bin[x] + 1]);
}
int main() {
  n = rd();
  m = rd();
  lg[0] = -1;
  for (int i = 1; i <= n; ++i)
    lg[i] = lg[i >> 1] + 1;
  bin[0] = 1;
  for (int i = 1; i <= 17; ++i)
    bin[i] = bin[i - 1] << 1;
  for (int i = 1; i <= n; ++i)
    mn[0][i] = mx[0][i] = rd();
  for (int i = 1; i <= lg[n]; ++i)
    for (int j = 1; j + bin[i] - 1 <= n; ++j)
      mx[i][j] = max(mx[i - 1][j], mx[i - 1][j + bin[i - 1]]),
      mn[i][j] = min(mn[i - 1][j], mn[i - 1][j + bin[i - 1]]);
  while (m--) {
    int l = rd(), r = rd();
    printf("%d\n", ask(l, r));
  }
  return 0;
}