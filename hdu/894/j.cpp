#include <cstdio>

const int DX[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int DY[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    scanf("%d%d", &n, &m);
    char map[110][110];
    for (int i = 1; i <= n; ++i)
      scanf("%s", map[i] + 1), map[i][0] = map[i][m + 1] = '*';
    for (int i = 0; i <= m + 1; ++i)
      map[0][i] = map[n + 1][i] = '*';
    char tar[10][10];
    scanf("%s%s%s", tar[1] + 1, tar[2] + 1, tar[3] + 1);
    int ans = 0;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j) {
        // printf("%d %d\n", i, j);
        bool flag = true;
        for (int k = 0; k < 8; ++k) {
          int x = i + DX[k], y = j + DY[k];
          int _x = 2 + DX[k], _y = 2 + DY[k];
          if (tar[_x][_y] != 'P' && tar[_x][_y] != map[x][y]) {
            flag = false;
            break;
          }
        }
        if (tar[2][2] == 'P' && map[i][j] == '#')
          flag = false;
        if (flag)
          ++ans;
      }
    printf("%d\n", ans);
  }
  return 0;
}
