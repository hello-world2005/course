#include <algorithm>
#include <cstdio>

const int N = 4e3 + 10;

char s1[N], s2[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    scanf("%s%s", s1 + 1, s2 + 1);
    int ans = 0;
    for (int d = 0; d <= std::min(n, m); ++d) {}
    printf("%d\n", ans);
  }
  return 0;
}
