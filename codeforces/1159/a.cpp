#include <algorithm>
#include <cstdio>

int main() {
  int n;
  char s[110];
  scanf("%d%s", &n, s + 1);
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    ans += (s[i] == '+' ? 1 : -1), ans = std::max(ans, 0);
  printf("%d\n", ans);
  return 0;
}
