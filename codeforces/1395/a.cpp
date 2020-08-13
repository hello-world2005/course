#include <cstdio>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    int cnt1 = (a & 1) + (b & 1) + (c & 1) + (d & 1);
    if (a && b && c)
      --a, --b, --c, d += 3;
    int cnt2 = (a & 1) + (b & 1) + (c & 1) + (d & 1);
    printf("%s\n", (cnt1 <= 1) || (cnt2 <= 1) ? "Yes" : "No");
  }
  return 0;
}
