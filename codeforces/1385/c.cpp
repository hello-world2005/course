#include <cstdio>
#include <cstring>

const int N = 2e5 + 10;

int a[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    a[n + 1] = 0;
    bool flag = true;
    for (int i = n; i >= 1; --i)
      if (flag) {
        if (a[i] >= a[i + 1])
          flag = true;
        else
          flag = false;
      } else if (a[i] > a[i + 1]) {
        printf("%d\n", i);
        goto ed;
      }
    printf("0\n");
  ed:;
  }
  return 0;
}