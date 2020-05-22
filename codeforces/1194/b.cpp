#include <algorithm>
#include <cstdio>
#include <vector>

const int N = 5e4 + 10;

int n, m;
std::vector<char> a[N];
int sx[N], sy[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
      a[i].resize(m + 2);
      getchar();
      for (int j = 1; j <= m; ++j)
        scanf("%c", &a[i][j]);
    }
    int cnt_x = 0, cnt_y = 0, p_x = 1, p_y = 1;
    for (int i = 1; i <= n; ++i) {
      int sum = 0;
      for (int j = 1; j <= m; ++j)
        sum += (a[i][j] == '*');
      sx[i] = sum;
    }
    for (int i = 1; i <= m; ++i) {
      int sum = 0;
      for (int j = 1; j <= n; ++j)
        sum += (a[j][i] == '*');
      sy[i] = sum;
    }
    // int ans = n + m - cnt_x - cnt_y;
    // if (!a[p_x][p_y])
    //   ++ans;
    // printf("%d %d %d %d\n", cnt_x, p_x, cnt_y, p_y);
    // if (ans == 0) {
    //   printf("%d\n", ans);
    // } else {
    //   if (a[p_x][p_y] == '.')
    //     --ans;
    //   printf("%d\n", ans);
    // }
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j) {
        int now = n + m - sx[i] - sy[j];
        if (a[i][j] == '.')
          --now;
        ans = std::min(ans, now);
      }
    printf("%d\n", ans);
    for (int i = 1; i <= n; ++i)
      a[i].clear(), sx[i] = 0;
    for (int i = 1; i <= m; ++i)
      sy[i] = 0;
  }
  return 0;
}

// 3 3
// ..*
// *..
// ..*
