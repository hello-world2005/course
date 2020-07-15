#include <bits/stdc++.h>

#define rd(x) x = read()

#define inf 0x3f3f3f3f3f3f3f3fLL
#define int long long
#define N 300005
#define M 35

using namespace std;

int n, m, x;
int a[N], s[N];
int f[N][M], h[N][M];

inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch > '9' || ch < '0') {
    if (ch == '-')
      f = -1;
    ch = getchar();
    if (ch == -1)
      return 0;
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}

inline void write(int x) {
  if (x < 0) {
    putchar('-');
    x = -x;
  }
  if (x >= 10)
    write(x / 10);
  putchar(x % 10 + '0');
}

int ans = -inf;

signed main() {
  rd(n), rd(m), rd(x);
  for (int i = 1; i <= n; i++)
    rd(a[i]), s[i] = s[i - 1] + a[i];
  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= m; j++) {
      f[i][j] = -inf;
      if (j == 0)
        f[i][j] = max(a[i], f[i - 1][j] + a[i]);
      else
        f[i][j] = max(f[i - 1][j] + a[i], h[i - 1][j - 1] + s[i] * x);
      h[i][j] = max(max(0ll, f[i][j]) - s[i] * x, h[i - 1][j]);
    }
  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= m; j++)
      ans = max(ans, f[i][j]);
  cout << ans << endl;
  return 0;
}