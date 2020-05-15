#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 110;
const int DX[] = {-1, 0, 0, 1};
const int DY[] = {0, -1, 1, 0};

int n, m, k;
char s[N][N];
int vis[N][N];
// void Dfs(int x, int y, int idx) {
//   // printf("%d %d %d %d\n", x, y, idx, cnt);
//   if (vis[x][y])
//     return;
//   if (!cnt && s[x][y] == 'R')
//     return;
//   if (s[x][y] == 'R')
//     --cnt;
//   vis[x][y] = idx;
//   for (int i = 0; i < 4; ++i) {
//     int _x = x + DX[i], _y = y + DY[i];
//     if (_x < 1 || _x > n || _y < 1 || _y > m)
//       continue;
//     Dfs(_x, _y, idx);
//   }
// }

void Print(int x) {
  if (x <= 10)
    printf("%c", x + '0' - 1);
  else if (x <= 36)
    printf("%c", x - 10 + 'a' - 1);
  else
    printf("%c", x - 36 + 'A' - 1);
}

int cnt[100];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    memset(vis, 0, sizeof(vis));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
      scanf("%s", s[i] + 1);
    int sum_r = 0;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        if (s[i][j] == 'R')
          ++sum_r;
    int r1 = sum_r / k, r2 = sum_r % k;
    int _cnt = 0;
    bool flag = true;
    int now = 1;
    for (int i = 1; i <= r2; ++i)
      cnt[i] = r1 + 1;
    for (int i = r2 + 1; i <= k; ++i)
      cnt[i] = r1;
    for (int i = 1; i <= n; ++i) {
      // int cnt = (now <= r2 ? r1 + 1 : r1);
      if (flag) {
        for (int j = 1; j <= m; ++j) {
          vis[i][j] = std::min(now, k);
          if (s[i][j] == 'R') {
            --cnt[now];
            if (cnt[now] == 0)
              ++now;
          }
        }
      } else {
        for (int j = m; j >= 1; --j) {
          vis[i][j] = std::min(now, k);
          if (s[i][j] == 'R') {
            --cnt[now];
            if (cnt[now] == 0) 
              ++now;
          }
        }
      }
      flag ^= 1;
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j)
        Print(vis[i][j]);
      printf("\n");
    }
  }
  return 0;
}
