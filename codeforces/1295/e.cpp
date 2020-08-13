#include <algorithm>
#include <cstdio>

const int N = 2e5 + 10;

int a[N], p[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &p[i]);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  int ans = 0x3f3f3f3f;
  for (int i = 1; i <= n; ++i)
    ans = std::min(ans, Solve(i));
  printf("%d\n", ans);
}
