#include <cstdio>
#include <cmath>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, d;
    scanf("%d%d", &n, &d);
    // if (n * 2 <= d)
    //   printf("YES\n");
    // else
    //   printf("NO\n");
    if (ceil(sqrt(d) * 2) <= n + 1)
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}
