#include <algorithm>
#include <cstdio>
#include <map>

const int N = 2e5 + 10;

int a[N];
std::map<int, bool> used;

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    used.clear();
    int n, ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) {
      if (used[a[i]])
        continue;
      int t = a[i];
      while (!(a[i] & 1)) {
        if (used[a[i]])
          break;
        ++ans;
        a[i] >>= 1;
      }
      used[t] = true;
    }
    printf("%d\n", ans);
  }
  return 0;
}
