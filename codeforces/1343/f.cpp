#include <cstdio>
#include <cstring>

const int N = 210;

int a[N];
int b[N][N];

int ans[N], pos[N];

bool Check(int n) {
  for (int i = 2; i <= n; ++i) {
    for (int j = 2; j <= n; ++j) {
      int used = 0, len = b[j][0];
      for (int k = 1; k <= b[j][0]; ++k) {
        if (!pos[b[j][k]])
          used = b[j][k];
        else if (pos[b[j][k]] >= i - b[j][0] + 1)
          --len;
      }
      // ans[i] = used;
      if (len == 1 && used) {
        ans[i] = used, pos[used] = i;
        break;
      }
    }
    if (ans[i] == 0)
      return false;
  }
  return true;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 2, k; i <= n; ++i) {
      scanf("%d", &k), b[i][0] = k;
      for (int j = 1; j <= k; ++j)
        scanf("%d", &b[i][j]);
    }
    for (int i = 1; i <= n; ++i) {
      memset(ans, 0, sizeof(ans));
      memset(pos, 0, sizeof(pos));
      ans[1] = i, pos[i] = 1;
      if (Check(n))
        break;
    }
    for (int i = 1; i <= n; ++i)
      printf("%d ", ans[i]);
    printf("\n");
  }
  return 0;
}
