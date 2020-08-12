#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 10;

int a[N], b[N << 1], c[N << 1];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, k;
    scanf("%d%d", &n, &k);
    memset(b, 0, sizeof(b)), memset(c, 0, sizeof(c));
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    for (int i = 1; i <= n / 2; ++i) {
      ++b[a[i] + a[n - i + 1]];
      ++c[std::min(a[i], a[n - i + 1]) + 1];
      --c[std::max(a[i], a[n - i + 1]) + k + 1];
      --c[a[i] + a[n - i + 1]], ++c[a[i] + a[n - i + 1] + 1];
    }
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= (k << 1); ++i)
      c[i] += c[i - 1];
    for (int i = 1; i <= (k << 1); ++i)
      ans = std::min(ans, c[i] + ((n / 2 - b[i] - c[i]) << 1));
    printf("%d\n", ans);
  }
  return 0;
}
