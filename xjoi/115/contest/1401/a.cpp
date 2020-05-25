#include <cstdio>

const int N = 1e5 + 10;

int n, m;
int a[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i <= n; ++i)
    a[i] = 1;
  while (m--) {
    int s, t;
    scanf("%d%d", &s, &t);
    for (int i = s; i <= t; ++i)
      if (a[i] > 0)
        --a[i];
  }
  int ans = 0;
  for (int i = 0; i <= n; ++i)
    ans += a[i];
  printf("%d\n", ans);
  return 0;
}
