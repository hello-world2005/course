#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 10;

char s[N];
int a[3];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    memset(a, 0, sizeof(a));
    scanf("%s", s + 1);
    int n = strlen(s + 1), ans = n + 1;
    // for (int l = 1, r = 0; r <= n; ++l) {
    //   printf("%d %d\n", l, r);
    //   while (a[s[l] - '1'] > 1)
    //     ++l;
    //   ++a[s[++r] - '1'];
    //   if (a[0] && a[1] && a[2])
    //     ans = std::max(ans, r - l + 1);
    // }
    for (int i = 1; i <= n; ++i) {
      a[s[i] - '1'] = i;
      int now = n + 1;
      for (int j = 0; j < 3; ++j)
        now = std::min(now, a[j]);
      if(!now)
        continue;
      ans = std::min(ans, i - now + 1);
      // printf("%d\n", i - now + 1);
      if (ans == 3)
        break;
    }
    printf("%d\n", ans == n + 1 ? 0 : ans);
  }
  return 0;
}
