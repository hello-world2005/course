#include <algorithm>
#include <cstdio>

const int N = 110;

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    int l[N], r[N], a[N];
    int ans = 0x3f3f3f3f;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
      scanf("%d%d", &l[i], &r[i]);
    for (int i = 1; i <= m; ++i)
      a[i] = i;
    do {
      int res = 0;
      for (int i = 2; i <= m; ++i)
        res += abs(l[a[i]] - l[a[i - 1]]) + abs(r[a[i]] - r[a[i - 1]]);
      ans = std::min(ans, res);
    } while (std::next_permutation(a + 1, a + m + 1));
    printf("%d\n", ans);
  }
  return 0;
}