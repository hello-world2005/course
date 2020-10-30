#include <cstdio>

const int N = 1e6 + 10;

int p[N], sze;

int main() {
  int n, ans = 0;
  scanf("%d", &n);
  if (n == 3) {
    printf("2\n2 1 2\n2 1 2\n2 1 2\n");
    return 0;
  }
  int m = (n - 1) / 6, k = (n - 1) % 6;
  ans = (n - 1) / 6 * 5;
  ans += k % 6;
  if (k % 6 == 1)
    ++ans;
  printf("%d\n", ans);
  bool flag = false;
  for (int i = 1; i <= m; ++i) {
    int a = (i - 1) * 5 + 1, b = a + 1, c = b + 1, d = c + 1, e = d + 1;
    printf("2 %d %d\n2 %d %d\n2 %d %d\n2 %d %d\n2 %d %d\n", a, d, a, d, b, d, b, e, c, e);
    p[++sze] = a, p[++sze] = b, p[++sze] = c;
    if (k == 1 && i == m) {
      printf("2 %d %d\n2 %d %d\n", e + 1, e + 2, e + 1, e + 2);
      p[++sze] = e + 1;
      flag = true;
      break;
    }
    printf("2 %d %d\n", c, e);
  }
  if (!flag) {
    int a = m * 5 + 1, b = a + 1, c = b + 1, d = c + 1, e = d + 1;
    switch (k) {
      case 2:
        printf("2 %d %d\n2 %d %d\n", a, b, a, b);
        p[++sze] = a;
        break;
      case 3:
        printf("2 %d %d\n2 %d %d\n2 %d %d\n", a, b, a, b, b, c);
        p[++sze] = a, p[++sze] = c;
        break;
      case 4:
        printf("2 %d %d\n2 %d %d\n2 %d %d\n2 %d %d\n", a, b, a, b, c, d, c, d);
        p[++sze] = a, p[++sze] = c;
        break;
      case 5:
        printf("2 %d %d\n2 %d %d\n2 %d %d\n2 %d %d\n2 %d %d\n", a, b, a, b, b, c, c, d, d, e);
        p[++sze] = a, p[++sze] = c, p[++sze] = e;
        break;
    }
  }
  printf("%d ", sze);
  for (int i = 1; i <= sze; ++i)
    printf("%d ", p[i]);
  printf("\n");
  return 0;
}
