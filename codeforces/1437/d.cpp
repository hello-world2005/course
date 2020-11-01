#include <cstdio>

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
    int ans = 0, lst = 1, ed = 1, k = 1;
    for (int i = 2; i < n; ++i) {
      if (a[i] < a[i + 1]) {
        ++lst;
      } else {
        if (k == ed)
          ++ans;
        --ed;
        if (ed == 0)
          k = ed = lst, lst = 1;
        else
          ++lst;
      }
    }
    if (lst)
      if (k == ed)
        ++ans;
    printf("%d\n", ans);
  }
  return 0;
}
