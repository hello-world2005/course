#include <cstdio>
#include <vector>

const int N = 4e5 + 10;

int n;
int a[N];
int sze[N], b[N];

int main() {
  int T;
  scanf("%d", &T);
  a[0] = -1;
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    int cnt = 0, sum = 0, tot = 0;
    for (int i = 1; i <= n; ++i)
      if (a[i] != a[i - 1])
        b[++cnt] = a[i], sze[cnt] = 1;
      else
        ++sze[cnt];
    for (int i = 1; i <= cnt; ++i) {
      if (sum + sze[i] <= n / 2)
        ++tot, sum += sze[i];
      else
        break;
    }
    if (tot < 3) {
      printf("0 0 0\n");
    } else {
      if (sze[1] >= sum - sze[1] - sze[2] && sze[1] >= sze[2]) {
        printf("0 0 0\n");
      } else {
        int au = sze[1], ag = 0;
        for (int i = 2; i <= tot; ++i) {
          ag += sze[i];
          if (ag > au)
            break;
        }
        if (!au || !ag || au + ag == sum || au >= ag || au >= sum - au - ag)
          printf("0 0 0\n");
        else
          printf("%d %d %d\n", au, ag, sum - au - ag);
      }
    }
    for (int i = 1; i <= cnt; ++i)
      sze[i] = 0;
  }
  return 0;
}
