#include <algorithm>
#include <cstdio>

int main() {
  int n, m;
  int a[3010];
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i)
    scanf("%d", &a[i]);
  std::sort(a + 1, a + m + 1);
  if (a[1] == 1 || a[m] == n)
    return printf("NO\n"), 0;
  for (int i = 1, cnt; i <= m; ++i) {
    if (a[i] == a[i - 1] + 1)
      ++cnt;
    else
      cnt = 0;
    if (cnt == 2)
      return printf("NO\n"), 0;
  }
  return printf("YES\n"), 0;
}
