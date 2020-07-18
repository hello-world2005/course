#include <algorithm>
#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int x, y, z, a, b, c;
    scanf("%d%d%d", &x, &y, &z);
    a = std::min(x, y), b = std::min(x, z), c = std::min(y, z);
    if (std::max(a, b) != x || std::max(b, c) != z || std::max(a, c) != y)
      printf("NO\n");
    else
      printf("YES\n%d %d %d\n", std::min(x, y), std::min(x, z), std::min(y, z));
  }
  return 0;
}
