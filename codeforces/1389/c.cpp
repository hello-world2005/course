// 95831 -> 58931
//          19583

#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 10;

char s[N];
int a[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    int n = strlen(s + 1), ans = 0;
    for (int i = 1; i <= n; ++i)
      a[i] = s[i] - '0';
    for (int i = 0; i <= 9; ++i)
      for (int j = 0; j <= 9; ++j)
        if (i != j) {
          int sum = 0;
          bool flag = true;
          for (int k = 1; k <= n; ++k)
            if (!flag) {
              if (a[k] == j)
                flag = true, sum += 2;
            } else {
              if (a[k] == i)
                flag = false;
            }
          ans = std::max(ans, sum);
        } else {
          int sum = 0;
          for (int k = 1; k <= n; ++k)
            if (a[k] == i)
              ++sum;
          ans = std::max(ans, sum);
        }
    printf("%d\n", n - ans);
  }
  return 0;
}
