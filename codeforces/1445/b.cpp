#include <algorithm>
#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    printf("%d\n", std::max(a + b, c + d));
  }
  return 0;
}
