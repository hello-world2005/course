#include <algorithm>
#include <cstdio>

const int N = 1e5 + 10;

char s[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d%s", &n, s + 1);
    int ans = 0;
    for (int i = 2; i <= n; ++i)
      ans += (s[i] == s[i - 1]);
    printf("%d\n", (ans + 1) >> 1);
  }
  return 0;
}
