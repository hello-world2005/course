#include <algorithm>
#include <cstdio>

const int N = 3e5 + 10;

int n;
int a[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  int ans = 0x3f3f3f3f;
  for (int i = 1; i <= n; ++i)
    ans = std::min(ans, a[i] / std::max(i - 1, n - i));
  printf("%d\n", ans);
  return 0;
}
