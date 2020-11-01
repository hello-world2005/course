#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int l, r;
    scanf("%d%d", &l, &r);
    if (l * 2 > r)
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}
