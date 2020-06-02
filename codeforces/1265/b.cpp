#include <cstdio>

const int N = 2e5 + 10;

int n;
int a[N];
int s[N], top;
int l[N], r[N];
int ans[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i) {
      while (top && a[s[top]] <= a[i])
        r[s[top--]] = i - 1;
      l[i] = s[top] + 1;
      s[++top] = i;
    }
    while (top)
      r[s[top--]] = n;
    for (int i = 1; i <= n; ++i)
      if (r[i] - l[i] + 1 == a[i])
        ans[a[i]] = 1;
    for (int i = 1; i <= n; ++i)
      printf("%d", ans[i]), ans[i] = 0;
    printf("\n");
  }
  return 0;
}
